import plotly.plotly as py
import plotly.graph_objs as go

#Read in expression levels with genes
def readInData(fileName, zValues):
    zValues = []
    print("Reading in data")
    f = open(fileName, 'r')
    
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
def heatMap():
    trace = go.Heatmap()
    data = [trace]
    py.plot(data, "basic-heatmap")
