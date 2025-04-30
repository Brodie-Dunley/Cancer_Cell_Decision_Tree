/**	file PatientLogic.h
	author :
	date :
	purpose: Defines the Patient sturct and specifies the logic that the tree will use
*/
#pragma once
#include <iostream>
class PatientLogic {
	int total_patients = 0;
	int invalid_patients = 0;
	int total_malignants = 0;
	int total_benigns = 0;
public:

	//Getter and setter methods for accessing Total amount of patients processed
	int get_total_patients() { return total_patients; }
	void increment_total_patients() { total_patients++; }

	//Getter and setter methods for accessing total amount of invalid patients processed
	int get_total_invalid() { return invalid_patients; }
	void increment_total_invalidpatients() { invalid_patients++; }


	//Getter and setter methods for accessing total amount of malignant cases processed
	int get_total_malignants() { return total_malignants; }
	void increment_total_malignant() { total_malignants++; }

	//Getter and setter methods for accessing total amount of Benign cases processed
	int get_total_benigns() { return total_benigns; }
	void increment_total_benign() { total_benigns++; }

	//patient class to create an object to examine
	struct patient
	{
	public:
		
		int patient_code;
		int clump_thickness;
		//Uniformity of cell size
		int UOFSize;
		//Uniformity of cell shape
		int UOFShape;
		int marginal_adhesion;
		//single epithelial cell size
		int epithelial_cell_size;
		int bare_nuclei;
		int bland_chromatin;
		int normal_nuclei;
		int mitoses;
		//Variable that will hold 2(Benign) or 4(Malignant)
		int diagnosis;

		patient(): patient_code(0),clump_thickness(0),UOFSize(0),UOFShape(0),marginal_adhesion(0),epithelial_cell_size(0),bare_nuclei(0),bland_chromatin(0),normal_nuclei(0),mitoses(0),diagnosis(0){}
		patient(int pc, int ct, int usize, int ushape, int ma, int ecs, int bn, int bc, int nn, int m,int d) : patient_code(pc), clump_thickness(ct), UOFSize(usize), UOFShape(ushape), marginal_adhesion(ma), epithelial_cell_size(ecs), bare_nuclei(bn), bland_chromatin(bc), normal_nuclei(nn), mitoses(m), diagnosis(d) {}

		//Setter method to set the patients diagnosis with the appropriate code
		void set_diagnosis(int code) { diagnosis = code; }
	};

	struct Node {
	public:
		using processing_function_type = bool(*)(Node* node, const patient& patient);       
		processing_function_type internal_processing_function;
		Node* true_child;
		Node* false_child;

		Node(const processing_function_type processing_function, Node* true_node = nullptr, Node* false_node = nullptr) : internal_processing_function(processing_function), true_child(true_node), false_child(false_node) {}

		
		bool process(const patient& patient)
		{
			return internal_processing_function(this, patient);
		}
	};
	//Setting up the logic function for each node
	


};