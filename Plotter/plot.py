import plotly.plotly as py
import plotly.graph_objs as go

#Read in expression levels with genes
def readInData(fileName, zValues):
    zValues = []
    print("Reading in data")
    f = open(fileName, 'r')
    
    #Skip the header line
    line = f.readline()
    
    #Read each line
    line = f.readline()

    while line:
        numStr = line[line.index("\t"):]
        
        #DEBUG
        print(numStr)
        
        zValues.append(float(numStr))
        line = f.readline()

    f.close()

#sample heatmap
def heatMap(RS3, RS4):
    trace = go.Heatmap(z=[RS3, RS4])
    data = [trace]
    py.plot(data, filename="basic-heatmap")

#------ Start of execution --------
RS3 = []
RS4 = []
