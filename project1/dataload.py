import os
import pandas as pd
import sys

def load_data():
    filename = "Slashdot0902.xlsx"
    # Get the current working directory
    current_dir = os.getcwd()

    # Specify the relative file path to the Excel file
    file_path = os.path.join(current_dir, "data", filename)
    try:
        df = pd.read_excel(file_path)
    except:
        print("Error reading file")
        exit()
    FromNodeId = df['FromNodeId'].tolist()
    ToNodeId = df['ToNodeId'].tolist()  
    print("data loaded successfully\n")
    return FromNodeId, ToNodeId


# FromNodeId, ToNodeId = load_data()
# print("FromNodeId: " + str(FromNodeId))
# print("ToNodeId: " + str(ToNodeId))

