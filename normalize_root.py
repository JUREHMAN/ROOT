import ROOT
import random

def normalize_tree(input_filename, output_filename):
    # Open the input file
    input_file = ROOT.TFile.Open(input_filename, "READ")
    print("Opening the input root file..")
    
    input_tree = input_file.Get("Allincltag")
    print("Opening the tree ...") 
     
    # Calculate the number of entries to keep
    nentries = input_tree.GetEntries()
    n_selected = int(nentries*0.16)
    print("Selected the number of entries...")

    #To solve the problem of multiple trees creation for large number of entries
    input_tree.SetAutoSave(0)
    
    # Create a new file to store the output tree
    output_file = ROOT.TFile(output_filename, "RECREATE")
    print("Creating the output file...")
    
    output_tree = input_tree.CopyTree(selection="", option="", nentries=n_selected, firstentry=0)
    print("Creating the output tree....")
    
    # Write the new tree to the output file
    output_tree.Write()
    print("Writing the output tree...")
    
    # Close the files
    output_file.Close()
    input_file.Close()
    print("Closing the input and output files...")

if __name__ == "__main__":
    input_filename = "uds_six_streams_with_sin_phi_less_than_one_cut.root"  
    output_filename = "uds_norm_one_sixth.root" 

    normalize_tree(input_filename, output_filename)

