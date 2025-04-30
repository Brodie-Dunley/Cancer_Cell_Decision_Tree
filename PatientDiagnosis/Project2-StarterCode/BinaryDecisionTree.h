/**	file BinaryDecisionTree.h
	author:	Brodie Dunley
	date  :	November 28, 2024
	purpose: Establishes the binary logic for the Decision Tree node
*/

#include <vector>
#include "PatientLogic.h"
//Setting up the class for the binary decision node
template<typename T>
class BinaryDecisionTree
{
public:
	using branch_logic_function = bool(*)(T&);
	using const_branch_logic_function = bool(*)(const T&);

protected:
	BinaryDecisionTree* true_branch_;
	BinaryDecisionTree* false_branch_;
	branch_logic_function logic_function_;
	const_branch_logic_function const_logic_function_;

public:
	BinaryDecisionTree(const branch_logic_function logic_func, BinaryDecisionTree* true_node = nullptr, BinaryDecisionTree* false_node = nullptr)
		:logic_function_(logic_func),
		const_logic_function_(nullptr), true_branch_(true_node), false_branch_(false_node)
	{
	}

	BinaryDecisionTree(const const_branch_logic_function logic_func, BinaryDecisionTree* true_node = nullptr, BinaryDecisionTree* false_node = nullptr)
		: logic_function_(nullptr), const_logic_function_(logic_func), true_branch_(true_node), false_branch_(false_node)
	{
	}
	BinaryDecisionTree()  {}

	void deleteTree(BinaryDecisionTree* node)
	{
		if (node)
		{
			deleteTree(node->true_branch_);
			deleteTree(node->false_branch_);
			delete node;
		}
	}
	~BinaryDecisionTree()
	{
		
	}

	bool process(T& data)
	{
		//call the linked functions
		bool result = false;
		if (logic_function_)
		{
			result = logic_function_(data);
		}
		else if (const_logic_function_)
		{
			result = const_logic_function_(data);
		}

		//use the result to see if we have anywhere to go next
		if (result)
		{
			if (true_branch_)
			{
				return true_branch_->process(data);
			}
		}
		else
		{
			if (false_branch_)
			{
				return false_branch_->process(data);
			}
		}

		//nowhere else to go, so return result of all to logic_function_(...)
		return result;
	}
	static bool marginal_adhesion(PatientLogic::patient& patient)
	{
		return patient.marginal_adhesion > 5;
	}
	//Uniformity of cell size
	static bool uniformity_of_Cs(PatientLogic::patient& patient)
	{
		
		return patient.UOFSize > 3;
	}
	//Clump thickness on the >2 bare nuclei branch
	static bool BN_G2_clump_thickness(PatientLogic::patient& patient)
	{
		return patient.clump_thickness >6;
	}
	//Clump thickness on the <=2 bare nuclei branch
	static bool BN_L2_clump_thickness(PatientLogic::patient & patient)
	{
		
		return patient.clump_thickness > 3;
	}
	static bool BN_L2_marginal_adhesion(PatientLogic::patient& patient)
	{

		return patient.marginal_adhesion > 3;
	}
	//Bare Nuclei on the >2 uniformity of cell size
	static bool G2_bare_nuclei(PatientLogic::patient & patient)
	{
		
		return patient.bare_nuclei >2;
	}
	//Uniformity of cell size after uniformity of cell shape to the right of the root
	static bool UCS_G2_Uniformity_of_cell_size(PatientLogic::patient& patient)
	{

		return patient.UOFSize <=4 ;
	}
	//clump thickness on the <=2 uniformity of cell shape branch
	static bool UCS_G2_clump_thickness(PatientLogic::patient & patient)
	{
		
		return patient.clump_thickness > 5;

	}
	static bool uniformity_of_cell_shape(PatientLogic::patient & patient)
	{
		
		return patient.UOFShape <= 2;
	}
	//Top of the tree from the right side above this point

	//Starting at the leaf node of the left side here:
	static bool L2_marginal_adhesion(PatientLogic::patient & patient)
	{
		
		return patient.marginal_adhesion <=3;
	}
	static bool bland_chromatin(PatientLogic::patient & patient)
	{
		return patient.bland_chromatin <=2;
	}
	//Clump thickness on the <=2 side of uniformity of cell size
	static bool L2_clump_thickness(PatientLogic::patient & patient)
	{
		
		return patient.clump_thickness <= 3;
	}
	//Bare nuclei on the <=2 side of uniformity of cell size
	static bool L2_bare_nuclei(PatientLogic::patient & patient)
	{
		return patient.bare_nuclei >3;
	}

	//The root of the tree
	static bool uniformity_cell_size(PatientLogic::patient & patient)
	{
		
		return patient.UOFSize <= 2;
	}

	//Terminal Nodes
	static bool malignant(PatientLogic::patient & patient)
	{
		patient.set_diagnosis(4);
		return false;
	}
	static bool benign(PatientLogic::patient & patient)
	{
		patient.set_diagnosis(2);

		return true;
	}
	static BinaryDecisionTree* buildTree()
	{
		//Leaf Nodes
		BinaryDecisionTree<PatientLogic::patient> benign_node;
		benign_node.logic_function_ = benign;
		benign_node.true_branch_ = nullptr;
		benign_node.false_branch_ = nullptr;

		BinaryDecisionTree<PatientLogic::patient> malignant_node; 
		malignant_node.logic_function_ = malignant;
		malignant_node.true_branch_ = nullptr;
		malignant_node.false_branch_ = nullptr;

		//Internal Nodes
		//Furthest Depth in the tree(5)
		BinaryDecisionTree<PatientLogic::patient>marginal_adhesion_node;
		marginal_adhesion_node.logic_function_ = marginal_adhesion;
		marginal_adhesion_node.true_branch_ = new BinaryDecisionTree(malignant_node);
		marginal_adhesion_node.false_branch_ = new BinaryDecisionTree(benign_node);
		
		//Layer(4)
		//Uniformity of cell size node
		BinaryDecisionTree<PatientLogic::patient>uniforimity_OCS_Node;
		uniforimity_OCS_Node.logic_function_ = uniformity_of_Cs;
		uniforimity_OCS_Node.true_branch_ = new BinaryDecisionTree(marginal_adhesion_node);
		uniforimity_OCS_Node.false_branch_ = new BinaryDecisionTree(malignant_node);

		//Clump thickness left branch of bare nuclei
		BinaryDecisionTree<PatientLogic::patient>BN_G2_clump_thickness_Node;
		BN_G2_clump_thickness_Node.logic_function_ = BN_G2_clump_thickness;
		BN_G2_clump_thickness_Node.true_branch_ = new BinaryDecisionTree(malignant_node);
		BN_G2_clump_thickness_Node.false_branch_ = new BinaryDecisionTree(uniforimity_OCS_Node);

		
		//Clump Thickness right branch from Bare Nuclei
		BinaryDecisionTree<PatientLogic::patient>BN_L2_marginal_adhesion_Node;
		BN_L2_marginal_adhesion_Node.logic_function_ = BN_L2_marginal_adhesion;
		BN_L2_marginal_adhesion_Node.true_branch_ = new BinaryDecisionTree(malignant_node);
		BN_L2_marginal_adhesion_Node.false_branch_ = new BinaryDecisionTree(benign_node);

		//Bare Nuclei, Right branch from uniformity of cell shape
		BinaryDecisionTree<PatientLogic::patient>G2_bare_nuclei_Node;
		G2_bare_nuclei_Node.logic_function_ = G2_bare_nuclei;
		G2_bare_nuclei_Node.true_branch_ = new BinaryDecisionTree(BN_G2_clump_thickness_Node);
		G2_bare_nuclei_Node.false_branch_ = new BinaryDecisionTree(BN_L2_marginal_adhesion_Node);


		//Clump Thickness, left branch of uniformity of cell shape
		BinaryDecisionTree<PatientLogic::patient>UCS_G2_clump_thickness_Node;
		UCS_G2_clump_thickness_Node.logic_function_ = UCS_G2_clump_thickness;
		UCS_G2_clump_thickness_Node.true_branch_ = new BinaryDecisionTree(malignant_node);
		UCS_G2_clump_thickness_Node.false_branch_ = new BinaryDecisionTree(benign_node);

		//Uniformity of cell size node after uniformity of cell shape node
		BinaryDecisionTree<PatientLogic::patient>UCS_G2_Uniformity_of_cell_size_Node;
		UCS_G2_Uniformity_of_cell_size_Node.logic_function_ = UCS_G2_Uniformity_of_cell_size;
		UCS_G2_Uniformity_of_cell_size_Node.true_branch_ = new BinaryDecisionTree(G2_bare_nuclei_Node);
		UCS_G2_Uniformity_of_cell_size_Node.false_branch_ = new BinaryDecisionTree(malignant_node);

		BinaryDecisionTree<PatientLogic::patient>uniformity_of_cell_shape_Node;
		uniformity_of_cell_shape_Node.logic_function_ = uniformity_of_cell_shape;
		uniformity_of_cell_shape_Node.true_branch_ = new BinaryDecisionTree(UCS_G2_clump_thickness_Node);
		uniformity_of_cell_shape_Node.false_branch_ = new BinaryDecisionTree(UCS_G2_Uniformity_of_cell_size_Node);

	

		//Starting to build the tree from the leaf nodes on the left side
		BinaryDecisionTree<PatientLogic::patient>L2_marginal_adhesion_Node;
		L2_marginal_adhesion_Node.logic_function_ = L2_marginal_adhesion;
		L2_marginal_adhesion_Node.true_branch_ = new BinaryDecisionTree(malignant_node);
		L2_marginal_adhesion_Node.false_branch_ = new BinaryDecisionTree(benign_node);


		BinaryDecisionTree<PatientLogic::patient>bland_chromatin_Node;
		bland_chromatin_Node.logic_function_ = bland_chromatin;
		bland_chromatin_Node.true_branch_ = new BinaryDecisionTree(L2_marginal_adhesion_Node);
		bland_chromatin_Node.false_branch_ = new BinaryDecisionTree(malignant_node);

		BinaryDecisionTree<PatientLogic::patient>L2_clump_thickness_Node;
		L2_clump_thickness_Node.logic_function_ = L2_clump_thickness;
		L2_clump_thickness_Node.true_branch_ = new BinaryDecisionTree(benign_node);
		L2_clump_thickness_Node.false_branch_ = new BinaryDecisionTree(bland_chromatin_Node);


		BinaryDecisionTree<PatientLogic::patient>L2_bare_nuclei_Node;
		L2_bare_nuclei_Node.logic_function_ = L2_bare_nuclei;
		L2_bare_nuclei_Node.true_branch_ = new BinaryDecisionTree(L2_clump_thickness_Node);
		L2_bare_nuclei_Node.false_branch_ = new BinaryDecisionTree(benign_node);

		//Root of the tree
		BinaryDecisionTree<PatientLogic::patient>root_node;
		root_node.logic_function_ = uniformity_cell_size;
		root_node.true_branch_ = new BinaryDecisionTree(L2_bare_nuclei_Node);
		root_node.false_branch_ = new BinaryDecisionTree(uniformity_of_cell_shape_Node);

		//Default point 
		return new BinaryDecisionTree(root_node);
		
	}
};


