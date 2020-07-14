#include "Preprocessor.h"
#include "Enumerations.h"

void Preprocessor::loadScan(Scan& scan, IOHandler& ioHandler) {

	const unsigned int numberOfcolumns = static_cast<unsigned int>(dataFormatA::NUMBER_OF_COLUMNS);

	std::string line;
	std::string blocks[numberOfcolumns];

	// Loop for iterating through dataset and processing data
	// TODO: Find alternative stratagy for adaptable parsing of data
	while (line != "EOF") {

		line = ioHandler.readData('\n');
		int start = 0;
		int length = 0;
		int j = 0;

		for (int i = 0; i < line.size(); i++) {

			length++;
			if ((line.at(i) == ',') || (line.at(i) == line.size() - 1)) {
				blocks[j] = line.substr(start, length);
				j++;
				start += length;
				length = 0;
			}
		}

		// Ignore data which is not a number
		// TODO: Find alternative stratagy for ignoring .csv header
		try {

			filterData(scan, blocks);

		}
		catch (std::exception &err)
		{
			// If block cannot be converted to double, then do nothing
			continue;
		}

	}

}

void Preprocessor::filterData(Scan& scan, std::string blocks[]) {

	// Input file config parameters
	const unsigned int columnX = static_cast<unsigned int>(dataFormatA::COLUMN_X);
	const unsigned int columnY = static_cast<unsigned int>(dataFormatA::COLUMN_Y);
	const unsigned int columnZ = static_cast<unsigned int>(dataFormatA::COLUMN_Z);
	const unsigned int columnDistance = static_cast<unsigned int>(dataFormatA::DISTANCE);
	const unsigned int columnIntensity = static_cast<unsigned int>(dataFormatA::INTENSITY);

	// Input data config parameters
	const unsigned int minDistance = static_cast<unsigned int>(algoParameters::MIN_DISTANCE);
	const unsigned int maxDistance = static_cast<unsigned int>(algoParameters::MAX_DISTANCE);
	const unsigned int minIntensity = static_cast<unsigned int>(algoParameters::MIN_INTENSITY);
	const unsigned int maxIntensity = static_cast<unsigned int>(algoParameters::MAX_INTENSITY);

	// Filtering logic
	bool distanceInRange = (std::stod(blocks[columnDistance]) <= maxDistance) && (std::stod(blocks[columnDistance]) > minDistance);
	bool intensityInRange = (std::stod(blocks[columnIntensity]) <= maxIntensity) && (std::stod(blocks[columnIntensity]) > minIntensity);

	// Filtering
	if (distanceInRange && intensityInRange) {

		Scan::Point point(std::stod(blocks[columnX]), std::stod(blocks[columnY]), std::stod(blocks[columnZ]));
		scan.m_data.push_back(point);

		point.printPoint();
	}
}