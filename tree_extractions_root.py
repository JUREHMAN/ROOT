###This script is intended to
#take an input root file with mutliple trees
#it will extract a single tree and produce a new root file

import ROOT
import sys

#defining the function
def tree_extraction(input_file_name,tree_to_extract,output_file_name):
    #opening the root file
    input_file = ROOT.TFile.Open(input_file_name)
    print(f"Opened the {input_file_name}") #this is an optional print statement to show the status of the program in the terminal
    
    #Extracting the desired tree from the input file
    input_tree = input_file.Get(tree_to_extract)
    print(f"Opened the {tree_to_extract}") #this is an optional print statement to show the status of the program in the terminal
    
    #creating the output file
    output_file = ROOT.TFile.Open(output_file_name,"RECREATE")
    print(f"Created the {output_file_name}") #this is an optional print statement to show the status of the program in the terminal
    
    #Clone the tree structure
    output_tree = input_tree.CloneTree(0)
    print(f"Cloned the {tree_to_extract} structure") #this is an optional print statement to show the status of the program in the terminal
    
    #writing the input tree to the output file
    for i in range(int(input_tree.GetEntries())):
        input_tree.GetEntry(i)
        output_tree.Fill()
   
    print("Filled the output tree")
    output_tree.Write()
   
    #closing the files
    print("CLosing the input and output files")
    input_file.Close()
    output_file.Close()
   
    print(f"Successfully extracted the {tree_to_extract} from {input_file_name} and created the {output_file_name}")
    print("Thank you for using this program")
# Usage example
if __name__ == "__main__":    
    if len(sys.argv) != 4:
        print("Usage: pyroot tree_extractions_root.py <input_file_name> <tree_to_extract> <output_file_name>")
    else:
        input_file_name = sys.argv[1]
        tree_to_extract = sys.argv[2]
        output_file_name = sys.argv[3]
        tree_extraction(input_file_name,tree_to_extract,output_file_name)
