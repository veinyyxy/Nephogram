#include "Proj4Transform.h"
#include <regex>
#include <sstream>

GROUND_NAMESPACE_START

Proj4Transform::Proj4Transform(void) : mSourceProjection(0), mDestinationProjection(0)
{
	m_TransType = TRANSFORM_2D;
}

Proj4Transform::~Proj4Transform(void)
{
	// free the proj objects
	if ( mSourceProjection != 0 )
	{
		pj_free( mSourceProjection );
	}
	if ( mDestinationProjection != 0 )
	{
		pj_free( mDestinationProjection );
	}
}

void Proj4Transform::setSourceCRS (std::string ProjString)
{
	strSourceProjection = ProjString;

	setSourceProjName(std::string("WGS84"));	
	projPJ pj = pj_init_plus(ProjString.c_str());
	mSourceProjection = pj;
	if ( mSourceProjection == NULL )
	{
		//qDebug("Set mSourceProjection fail");
	}
}

void ClipString(const std::string& inStr, std::vector<std::string>& outVector, const std::string& regexStr)
{
	std::regex re{ regexStr };
	std::vector<std::string> templist
	{
		std::sregex_token_iterator(inStr.begin(), inStr.end(), re, -1),
		std::sregex_token_iterator()
	};
	outVector = templist;
}

void Proj4Transform::setDestCRS (std::string ProjString)
{
	strDestinationProjection = ProjString;

	/*if(Pro_map.find(ProjString))
	{
	setDesProjName(Pro_map.find(ProjString).value());
	}*/

	std::string s_lat;
	std::string s_lon;
	int iLat = -1, iLon = -1;
	if (0 == strDestinationProjection.size()) return;
	std::string tempDestination(strDestinationProjection.c_str());
	//std::vector<std::string> templist = tempDestination.split(" ");
	std::vector<std::string> templist;
	ClipString(tempDestination, templist, " ");
	bool b_lat = false,b_lon = false;
	for(int i = 0; i < templist.size(); i++)
	{
		if(templist.at(i).find("+lat_0") != std::string::npos)
		{
			s_lat = templist.at(i);
			iLat = i;
			b_lat = true;
		}
		if(templist.at(i).find("+lon_0") != std::string::npos)
		{
			s_lon = templist.at(i);
			iLon = i;
			b_lon = true;
		}
	}

	if (b_lat)
	{
		//QStringList latlist = s_lat.split("=");
		std::vector<std::string> latlist;
		ClipString(s_lat, latlist, "=");
		m_lat = atof(latlist[1].c_str());
	}else
		m_lat = 0.0;

	if (b_lon)
	{
		//QStringList lonlist = s_lon.split("=");
		std::vector<std::string> lonlist;
		ClipString(s_lon, lonlist, "=");
		m_lon = atof(lonlist[1].c_str());
	}else
		m_lon = 0.0;


	mDestinationProjection = pj_init_plus(ProjString.c_str());
	if ( mDestinationProjection == NULL )
	{
		//qDebug("Set mDestinationProjection fail");
	}
}

osg::Vec3 Proj4Transform::Transform(const osg::Vec3 vertex)
{

	if ( mSourceProjection == mDestinationProjection) return vertex;

	x = vertex.x();
	z = vertex.y();
	y = vertex.z();

	transformCoords( 1, &x, &y, &z );

	return osg::Vec3(x, y, z);

}

osg::Vec3 Proj4Transform::Transform(double gLx, double gLy, double gLz)
{
	return Transform( osg::Vec3( (float)gLx, (float)gLy, (float)gLz ) );
}

//QRectF Proj4Transform::TransformBoundingBox(const QRectF rectangle, TRANSFORM_DIRECTION direction)
//{
//	if ( mSourceProjection == mDestinationProjection ) return rectangle;
//
//	xMAX = rectangle.right();
//	yMAX = rectangle.top();
//	xMIN = rectangle.left();
//	yMIN = rectangle.bottom();
//
//	z = 0.0;
//	transformCoords( 1, &xMAX, &yMAX, &z, direction );
//	transformCoords( 1, &xMIN, &yMIN, &z, direction );
//
//	return QRectF( xMIN, yMAX, xMAX - xMIN, yMAX - yMIN );
//
//}

int Proj4Transform::transformCoords( const int& numPoints, double *x, double *y, double *z)
{
	if ( mDestinationProjection == NULL )
	{
		//qDebug("DestinationProjection NULL");
		return 0;
	}
	if ( mSourceProjection == NULL )
	{
		//qDebug("SourceProjection NULL");
		return 0;
	}

	// use proj4 to do the transform
	// if the source/destination projection is lat/long, convert the points to radians prior to transforming
	if (pj_is_latlong( mSourceProjection ) )
	{
		for (i = 0; i < numPoints; ++i )
		{
			x[i] *= DEG_TO_RAD;
			y[i] *= DEG_TO_RAD;
			z[i] *= DEG_TO_RAD;
		}
	}

	
	projResult = pj_transform( mSourceProjection, mDestinationProjection, numPoints, 0, x, y, z );

	if ( projResult != 0 )
	{
		std::ostringstream ostrStream;
		//something bad happened....
		for ( int i = 0; i < numPoints; ++i )
		{
			ostrStream.clear();
			ostrStream<<"("<<x[i]<<", "<<y[i]<<")\n";
			points = ostrStream.str();
			
			ostrStream.clear();
			ostrStream<<x[i]<<"of "<<y[i]<<" failed with error: "<<pj_strerrno( projResult )<<'\n';
			msg = ostrStream.str();
			//qDebug("pj_transform fail");
			//qDebug()<<msg;
		}
		return 0;
	}
	// if the result is lat/long, convert the results from radians back to degrees
	if (pj_is_latlong( mDestinationProjection)
		|| pj_is_latlong( mSourceProjection ))
	{
		for ( int i = 0; i < numPoints; ++i )
		{
			x[i] *= RAD_TO_DEG;
			y[i] *= RAD_TO_DEG;
			z[i] *= RAD_TO_DEG;
		}
	}
	return 1;
}

int Proj4Transform::Transform( const osg::Vec3& src, osg::Vec3& dst )
{
	int projResult = 0;
	double dX, dY, dZ;

	if ( mDestinationProjection == NULL || mSourceProjection == NULL)
	{
		return projResult;
	}
	dX = src.x() * DEG_TO_RAD;
	dY = src.y() * DEG_TO_RAD;
	dZ = src.z() * DEG_TO_RAD;
	projResult = pj_transform(mSourceProjection, mDestinationProjection, 1, 0, &dX, &dY, &dZ);
	dst.set(dX, src.z(), dY);

	return projResult;
}

std::string Proj4Transform::ImportFromESRI(const char *  pszFname )
{
#if 0
	OGRSpatialReference projection;

	char **papszPrj = CSLLoad(pszFname); 

	OGRErr eErr = projection.importFromESRI(papszPrj); 

	CSLDestroy( papszPrj );
	char *destproj =NULL;
	projection.exportToProj4(&destproj);
	std::string temp ;	
	temp = destproj;
	return temp.trimmed();
#else
	std::string str;
	return str;
#endif
}

std::string Proj4Transform::getDesCRS()
{
	return strDestinationProjection;
}

std::string Proj4Transform::getSourceCRS()
{
	return strSourceProjection;
}

 std::string Proj4Transform::getDesProjName()
 {
 	return strDestinationProName;
 }
 
 std::string Proj4Transform::getSourceProjName()
 {
 	return strSourceProName;
 }

 void Proj4Transform::setSourceProjName(std::string ProjString)
 {
	 strSourceProName = ProjString;
 }

 void Proj4Transform::setDesProjName(std::string ProjString)
 {
	 strDestinationProName = ProjString;
 }

 bool Proj4Transform::setCenter( double lon,double lat  )
 {
	 std::string s_lat;
	 std::string s_lon;
	 int iLat = -1, iLon = -1;
	 if (0 == strDestinationProjection.size()) return false;
	 std::string tempDestination(strDestinationProjection.c_str());
	 std::vector<std::string> templist;// = tempDestination.split(" ");

	 ClipString(tempDestination, templist, " ");
	 for(int i = 0; i < templist.size(); i++)
	 {
		 if(templist.at(i).find("+lat_0") != std::string::npos)
		 {
			 s_lat = templist.at(i);
			 iLat = i;
		 }
		 if(templist.at(i).find("+lon_0") != std::string::npos)
		 {
			 s_lon = templist.at(i);
			 iLon = i;
		 }
	 }

	 //QStringList latlist = s_lat.split("=");
	 std::vector<std::string> latlist; ClipString(s_lat, latlist, "=");
	 m_lat = lat;
	 m_lon =lon;

	 std::stringstream ss;
	 ss << lat << "n";
	 ss >> latlist[1];
	 ss.clear();
	 //QStringList lonlist = s_lon.split("=");
	 std::vector<std::string> lonlist; ClipString(s_lon, lonlist, "=");

	 ss << lon << "e";
	 ss>>lonlist[1];
	 

	 templist[iLat] = latlist[0] + "=" +latlist[1];
	 templist[iLon] = lonlist[0] + "=" + lonlist[1];
	 //tempDestination = templist.join(" ");

	 std::for_each(templist.begin(), templist.end(), [&](const std::string& strText){
		 //tempDestination = tempDestination + " ";
		 tempDestination += strText;
		 tempDestination += " ";
	 });
	 setDestCRS(tempDestination);
	 return true;

 }


GROUND_NAMESPACE_END