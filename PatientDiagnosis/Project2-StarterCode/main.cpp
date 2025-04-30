/* main.cpp : This file contains the 'main' function.This will get the pathway of the csv file, send it to the appropriate file.Will also be used to output the final count of patients and the malignant and benign count
	
	Coder: Brodie Dunley
	Date: November 11, 2024
*/

#include <fstream>
#include <iostream>
#include <istream>
#include "Scanner.h"
#include "BinaryDecisionTree.h"
#include <ostream>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	PatientLogic patientlogic;
	std::cout << "Enter the File pathway to load in patient information: ";
	std::string filename;
	std::getline(std::cin, filename);
	//Change this to CIN later
	//std::string filename = "C:/Users/bdunl/Desktop/School Fall/Data Structures and algorithms/Project 2/unformatted_data_v1.0.0.csv";
	
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: unable to open the file" << std::endl;
		
	}
	//creating a vector list to hold all the patients created from the csv
	std::vector<PatientLogic::patient> patientList;
	ScanPatientData(file, patientList, patientlogic);

	
	int intake = patientlogic.get_total_patients();
	int invalid = patientlogic.get_total_invalid();
	int total = intake - invalid;
	
	//Looping through the patient list and building the tree
	for (auto& patient : patientList)
	{
		bool result = BinaryDecisionTree<PatientLogic::patient>::buildTree()->process(patient);
		if (result == true)
			patientlogic.increment_total_benign();
		else
			patientlogic.increment_total_malignant();
	}

	
	std::cout << "\nTotal Patients processed: " << total << std::endl;
	std::cout << "Total Benign: " << patientlogic.get_total_benigns() << std::endl;
	std::cout << "Total Malignant: " << patientlogic.get_total_malignants() << std::endl;
	std::cout << "Total Invalid patients: " << invalid << std::endl;
	
	//Saving to file: Name: results.csv
	std::string fileName = "results.csv";
	std::ofstream outFile(fileName);

	//If the file doesn't open then throw an error
	if (!outFile.is_open())
	{
		std::cerr << "Could not open the files!" << std::endl;
		
	}
	//Header files for the CSV file
	outFile << "Patient Code" << ", " << "Clump Thickness" << ", " << "Uniformity of Cell Size" << ", " << "Uniformity of Cell Shape" << ", " << "Marginal Adhesion" << ", " << "Single Epithelial Cell size" << ", " << "Bare Nuclei" << ", " << "Bland Chromatin" << ", " << " Normal Nucleoi" << ", " << "Mitoses" << "," << "Class" << "\n";

	//Loading the cSV file columns
		for (const auto& patient : patientList)
	{
		outFile << patient.patient_code << ", " << patient.clump_thickness << ", " << patient.UOFSize << ", " << patient.UOFShape << ", " << patient.marginal_adhesion << ", " << patient.epithelial_cell_size << ", " << patient.bare_nuclei << ", " << patient.bland_chromatin << ", " << patient.normal_nuclei << ", " << patient.mitoses << ", " << patient.diagnosis << "\n";
	}
		_CrtDumpMemoryLeaks();
		return 0;
}

