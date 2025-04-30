# Cancer_Cell_Decision_Tree
Given a .csv file with client information, determine whether or not the cancer biopsy is malignant or benign

This will demonstrate the use and implementation of a Decision Tree Data Mining Technique

Benign tumors have not yet spread to other parts of the body whereas Malignant tumors have already spread to other parts of the body. A study has been published that uses a Binary Decision tree to determine if a patient has benign or malignant breast cancer tumors to within a 94.5% accuracy.
This program will read in data from patients from a file, run it through the binary decision tree and output the results with the diagnosis Benign or Malignant.
The results will be stored in a file named results.csv. The result will be indicated by 2(meaning Benign) or 4(meaning malignant)

The results will be based on the following:

Uniformity of Cell Size <= 2 
 | -> Bare Nuclei <= 3 : Benign
 | -> Bare Nuclei > 3
 |    |  -> Clump Thickness <= 3: Benign
 |    |  -> Clump Thickness > 3
 |    |      -> Bland Chromatin <=2
 |    |        |   -> Marginal Adhesion <= 3: Malignant
 |    |        |   -> Marginal Adhesion > 3: Benign
 |    |        |
 |    |      -> Bland Chromatin > 2: Malignant
 Uniformity of Cell Size > 2
 |  -> Uniformity of Cell Shape <= 2
 |      |  -> Clump Thickness <= 5: Benign
 |      |  -> Clump Thickness > 5: Malignant
 |  -> Uniformity of Cell Shape > 2
 |      ->  Uniformity of Cell Size <= 4
 |          |  ->  Bare Nuclei <= 2
 |          |      |  ->  Marginal Adhesion <= 3: Benign
 |          |      |  ->  Marginal Adhesion > 3: Malignant
 |          |  -> Bare Nuclei >2
 |          |      |  -> Clump Thickness <= 6
 |          |      |      |  -> Uniformity of Cell Size <= 3: Malignant
 |          |      |      |  -> Uniformity of Cell Size > 3
 |          |      |      |      |  -> Marginal Adhesion <= 5: Benign
 |          |      |      |      |  -> Marginal Adhesion > 5: Malignant
 |          |      |  -> Clump Thickness > 6: Malignant
 |      ->  Uniformity of Cell Size > 4: Malignant





 
