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
	INTENSITY = 4,
	NUMBER_OF_COLUMNS = 9
};

enum class vehicleParameters : unsigned int
{
	SENSOR_HEIGHT = 3
};

#endif // !ENUMERATIONS