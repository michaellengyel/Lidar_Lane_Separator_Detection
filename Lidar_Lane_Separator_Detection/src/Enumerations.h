//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef ENUMERATIONS
#define ENUMERATIONS

//============================================================================================================
// The Enumerations .h holds parameters. This should be refactored to be provided by a config file.
// TODO: Switch to Doxygen format(///)
// Refactor to use constexpr instead of enums
//============================================================================================================

enum class dataFormatA : unsigned int
{
	COLUMN_X = 0,
	COLUMN_Y = 1,
	COLUMN_Z = 2,
	INTENSITY = 3,
	LASER_ID = 4,
	DISTANCE = 6,
	NUMBER_OF_COLUMNS = 9
};

enum class algoParameters : int
{
	MIN_DISTANCE = 0,
	MAX_DISTANCE = 255,

	MIN_INTENSITY = 0,
	MAX_INTENSITY = 255,

	MAX_X = 20,
	MIN_X = -20,
	MAX_Y = 30,
	MIN_Y = -20,
	MAX_Z = 20,
	MIN_Z = -20,

	//LASER_ID = 0
	USED_DUPLICATE = 0, // Which duplicate to use
	NUMBER_OF_DUPLICATES = 2 // Number of duplicates in data
};

enum class vehicleParameters : unsigned int
{
	SENSOR_HEIGHT = 3
};

constexpr bool g_filterDuplicateReturn = true; // Turn filtering of duplicates on and off

constexpr int g_points = 80000; // TODO: Refactor logic

#endif // !ENUMERATIONS