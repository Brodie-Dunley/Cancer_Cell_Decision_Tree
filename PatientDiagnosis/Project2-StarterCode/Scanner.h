/**	file Scanner.h
	author:	Brodie Dunley
	date  :	November 28, 2024
	purpose: Intake the csv file, scan through the file and laod the clients and their results. Validating data won't include any invalid data into the final container
*/
#pragma once


#include "PatientLogic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

void ScanPatientData(std::ifstream& file, std::vector<PatientLogic::patient>& patientList,PatientLogic& patientLogic)
{
	//Creating a container to store the CSV data
	std::vector<std::vector<std::string>> data;

	
	//Reading each line of the CSV file
	std::string line;
	while (std::getline(file, line))
	{
		
		//Vector to hold all the rows
		std::vector<std::string>row;
		std::istringstream linestream(line);
		//representing an indiviaul cell, therefore an individual value
		std::string cell;
		//Using a bool to keep track if the while looped exited, meaning bad data was found
		bool bad_data = false;
		std::vector<int> patient_data{};
		//Getting a row with CSV
		while (std::getline(linestream, cell, ','))
		{
			if(!cell.empty() && std::all_of(cell.begin(),cell.end(), ::isdigit))
				patient_data.push_back(stoi(cell));
				
			else
			{
				bad_data = true;
				break;
			}

		}
		if (bad_data != true)
		{
			//Create a patient and add it to the list
			
			int patient_code = patient_data[0];
			int	clump_thickeness = patient_data[1];
			int	UOFSize = patient_data[2];
			int	UOFShape = patient_data[3];
			int	marginal_adhesion = patient_data[4];
			int	epithelial_cell_size = patient_data[5];
			int	bare_nuclei = patient_data[6];
			int	bland_chromatin = patient_data[7];
			int	normal_nuclei = patient_data[8];
			int	mitoses = patient_data[9];
			int diagnosis = patient_data[10];
			PatientLogic::patient patient(patient_code, clump_thickeness, UOFSize, UOFShape, marginal_adhesion, epithelial_cell_size, bare_nuclei, bland_chromatin, normal_nuclei, mitoses,diagnosis);

			patientList.push_back(patient);
			patientLogic.increment_total_patients();
		}
		//If the data is invalid increment the totals but don't add to the vector
		else if (bad_data == true)
		{
			patientLogic.increment_total_patients();
			patientLogic.increment_total_invalidpatients();
		}
	}
}
	
