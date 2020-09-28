#pragma  once

#ifndef GEOSONTHEOSG_LIB
# define GROUND_EXPORT __declspec(dllexport)
#else
# define GROUND_EXPORT __declspec(dllimport)
#endif