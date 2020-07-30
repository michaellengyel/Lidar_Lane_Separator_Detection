#include "Preprocessor.h"

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

	// Filtering logic
	bool distanceInRange = (std::stod(blocks[m_columnDistance]) <= maxDistance) && (std::stod(blocks[m_columnDistance]) > minDistance);
	bool intensityInRange = (std::stod(blocks[m_columnIntensity]) <= maxIntensity) && (std::stod(blocks[m_columnIntensity]) > minIntensity);

	bool xInRange = (std::stod(blocks[m_columnX]) <= m_maxX) && (std::stod(blocks[m_columnX]) > m_minX);
	bool yInRange = (std::stod(blocks[m_columnY]) <= m_maxY) && (std::stod(blocks[m_columnY]) > m_minY);
	bool zInRange = (std::stod(blocks[m_columnZ]) <= m_maxZ) && (std::stod(blocks[m_columnZ]) > m_minZ);

	bool orthoInRange = (xInRange && yInRange && zInRange);

	// Duplicate filtering logic
	// TODO: Refactor
	bool readingDuplicate = true;

	if (filterDuplicateReturn) {
		trackDuplicate(blocks);
		readingDuplicate = m_readingDuplicate;
	}

	// Filtering
	if ((distanceInRange && intensityInRange) && (readingDuplicate && orthoInRange)) {

		Point point(std::stod(blocks[m_columnX]), std::stod(blocks[m_columnY]), std::stod(blocks[m_columnZ]));
		Scan::Pulse pulse(point);
		scan.m_data.push_back(point);

		// TODO: Remove debug function calls
		//point.printPoint();
	}
}

void Preprocessor::trackDuplicate(std::string blocks[]) {

	bool endOfFrame = (std::stod(blocks[m_columnLaserID]) <= m_previousID);
	bool notfilteredFrame = (m_duplicateCounter == m_usedDuplicate);

	m_previousID = (std::stod(blocks[m_columnLaserID]));

	if (endOfFrame) {
		// Increment or reset the counter
		if (m_duplicateCounter == (m_numberOfDuplicate - 1)) {
			m_duplicateCounter = 0;
		}
		else {
			m_duplicateCounter++;
		}

		if (notfilteredFrame) {
			m_readingDuplicate = true;
			//std::cout << "FALSE" << std::endl;
		}
		else {
			m_readingDuplicate = false;
			//std::cout << "TRUE" << std::endl;
		}
	}
	else {
		// Do Nothing
	}
}