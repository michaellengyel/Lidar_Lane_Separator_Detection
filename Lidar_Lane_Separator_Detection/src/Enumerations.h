//============================================================================================================
// Copyright Disclaimer Placeholder
//============================================================================================================

#ifndef ENUMERATIONS
#define ENUMERATIONS

//============================================================================================================
// The Enumerations .h holds parameters. This should be refactored to be provided by a config file.
// TODO: Switch to Doxygen format(///)
//============================================================================================================

enum class dataFormatA : unsigned int
{
	COLUMN_X = 0,
	COLUMN_Y = 1,
	COLUMN_Z = 2,
	INTENSITY = 3,
	DISTANCE = 6,
	NUMBER_OF_COLUMNS = 9
};

enum class algoParameters : unsigned int
{
	MIN_DISTANCE = 0,
	MAX_DISTANCE = 255,
	MIN_INTENSITY = 0,
	MAX_INTENSITY = 255
	//LASER_ID = 0
};

enum class vehicleParameters : unsigned int
{
	SENSOR_HEIGHT = 3
};

#endif // !ENUMERATIONS