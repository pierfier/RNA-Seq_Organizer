import plotly.plotly as py
import plotly.graph_objs as go

#Read in expression levels with genes
def readInData(fileName, zValues):
    zValues = []
    print("Reading in data")
    f = open(fileName, 'r')
    
    #Read each line
    while line = f.readline():
        numStr = 
        zValues.append(float(numStr))

#sample heatmap
def heatMap():
    trace = go.Heatmap()
    data = [trace]
    py.plot(data, "basic-heatmap")
