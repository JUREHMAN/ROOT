import ROOT

def copy_root_file_with_cut(input_filename, output_filename, cut):
    # Open the original ROOT file
    input_file = ROOT.TFile.Open(input_filename, "READ")
    print("Taken the input file ....")
    
    #Taking the input tree
    input_tree = input_file.Get("Allincltag")
    print("Taken the input tree ...")

    #ChatGBT suggestion (it solved the problem of multiple trees creation in case of large number of entries)
    input_tree.SetAutoSave(0)
    
    # Create a new ROOT file to store the output
    output_file = ROOT.TFile.Open(output_filename, "RECREATE")
    print("Creating the output file .....")
    
    #Creating the output tree
    output_tree = input_tree.CopyTree(cut)
    print("Created the output tree ...")
    
    output_tree.Write()
    print("Writing the output tree ...")

    # Close the files
    output_file.Close()
    print("closing the output file....")
    
    input_file.Close()
    print("closing the input file...")
    print(f"Output root file {output_filename} has been created with the cut {cut}")

if __name__ == "__main__":
    input_filename = "uds_six_streams_without_cuts_with_tag_ids.root"
    output_filename = "uds_six_streams_with_sin_phi_less_than_one_cut.root"
    cut = "sin_phi < 1.0"  # Apply the cut on the sinphi variable

    copy_root_file_with_cut(input_filename, output_filename, cut)

