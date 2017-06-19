from plotly.offline import plot
import plotly.graph_objs as go

#Read in expression levels with genes
def readInData(fileName, zValues):
    print("Reading in data")
    f = open(fileName, 'r')
    
    #Skip the header line
    line = f.readline()
    
    #Read each line
    line = f.readline()

    while line:
        
        numStr = line.split()[1]
        zValues.append(float(numStr))
        line = f.readline()

    f.close()

#sample heatmap
def heatMap(RS3, RS4):
    trace = go.Heatmap(z=[RS3, RS4])
    data = [trace]
    plot(data, filename="sample.html")

#------ Start of execution --------
RS3 = []
RS4 = []
readInData("sample1.txt", RS3)
readInData("sample2.txt", RS4)

heatMap(RS3, RS4)
