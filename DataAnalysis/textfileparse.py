

import os
import glob

i=0
j=0
k=0
# simName = ""
# ofile = ""
ipath = '../sim_results/'


# Open the cumulative file output file 'outfile'
cmltvfile = open("allData.csv",'w')
nameList = open("nameList.csv", 'w')

# Step through each file in the directory
for infile in glob.glob( os.path.join(ipath, '*.txt')):
    dataList = []
    ofile = ""
    #print("Reading: " + infile)

    # Open the current file: 'infile'
    tfile = open(infile,'r')



    # Read the important lines.
    for i, line in enumerate(tfile):
        line.lstrip()
        line = line.split()
        if i == 1:
            # Parse the name from the file, open a new file with that name
            simName = line[0]
            simName = simName.replace('.','_')
            ofile = simName + ".csv"
            nmStr = ofile + "\n"
            nameList.write(nmStr)
            #dataList.append(simName)
            #print("ofile: ", ofile)

        elif i == 9:
            L1size  = line[2]
            L1ways  = line[3]
            L1block = line[4]
            dataList.append(L1size)
            dataList.append(L1ways)
            dataList.append(L1block)

        elif i == 11:
            L2size  = line[2]
            L2ways  = line[3]
            L2block = line[4]
            dataList.append(L2size)
            dataList.append(L2ways)
            dataList.append(L2block)

        elif i == 20:
            execT = line[2]
            dataList.append(execT)

        elif i == 21:
            totRefs = line[2]
            dataList.append(execT)

        elif i == 22:
            numInstRefs = line[2]
            dataList.append(numInstRefs)

        elif i == 23:
            numDataRefs = line[2]
            dataList.append(numDataRefs)

        elif i == 30:
            numCReads = line[1]
            dataList.append(numCReads)

        elif i == 31:
            numCWrites = line[1]
            dataList.append(numCWrites)

        elif i == 32:
            numCInst = line[1]
            dataList.append(numCInst)

        elif i == 52:
            # execT on line 20
            cpi = line[2]
            dataList.append(cpi)

        elif i == 53:
            idealExecT = line[1]
            idealCPI = line[2]
            dataList.append(idealExecT)
            dataList.append(idealCPI)

        elif i == 54:
            idealMisAExecT = line[2]
            idealMisACPI = line[3]
            dataList.append(idealMisAExecT)
            dataList.append(idealMisACPI)

        elif i == 61:
            L1ihits = line[2]
            L1dhits = line[3]
            L2hits  = line[4]
            dataList.append(L1ihits)
            dataList.append(L1dhits)
            dataList.append(L2hits)

        elif i == 62:
            L1imiss = line[2]
            L1dmiss = line[3]
            L2miss  = line[4]
            dataList.append(L1imiss)
            dataList.append(L1dmiss)
            dataList.append(L2miss)

        elif i == 63:
            L1iTotReqs = line[2]
            L1dTotReqs = line[3]
            L2TotReqs  = line[4]
            dataList.append(L1iTotReqs)
            dataList.append(L1dTotReqs)
            dataList.append(L2TotReqs)

        elif i == 66:
            L1iKicks = line[1]
            L1dKicks = line[2]
            L2Kicks  = line[3]
            dataList.append(L1iKicks)
            dataList.append(L1dKicks)
            dataList.append(L2Kicks)

        elif i == 67:
            L1iDrtyKcks = line[2]
            L1dDrtyKcks = line[3]
            L2DrtyKcks  = line[4]
            dataList.append(L1iDrtyKcks)
            dataList.append(L1dDrtyKcks)
            dataList.append(L2DrtyKcks)

        elif i == 69:
            L1iVChit = line[3]
            L1dVChit = line[4]
            L2VChit  = line[5]
            dataList.append(L1iVChit)
            dataList.append(L1dVChit)
            dataList.append(L2VChit)

        elif i == 76:
            L1Cost = line[1]
            dataList.append(L1Cost)

        elif i == 77:
            L2Cost = line[1]
            dataList.append(L2Cost)

        elif i == 78:
            mMemCost = line[2]
            dataList.append(mMemCost)

        elif i == 80:
            numReads = line[1]
            dataList.append(numReads)


    # print("outfile name: ", ofile)

    outStr = " ".join(dataList)
    # outfile = open(ofile,'w')
    # outfile.write(outStr)
    # outfile.close()

    cmltvfile.write(outStr + "\n")
    # print(dataList)
    # input()


tfile.close()
cmltvfile.close()
nameList.close()
