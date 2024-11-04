#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
// #include <filesystem>

struct Node
{
    std::vector<double> centroid;
    int index;
    std::vector<int> iFaces;
    std::vector<int> iElements;
};

class Mesh
{
    private:
        std::string caseDirectory_;
        // int numberofNodes;
        std::vector<Node>& nodes_; 

    public:
        Mesh(std::string caseDir, std::vector<Node>& points)
        :caseDirectory_(caseDir), nodes_(points)
        {}

        std::vector<Node>& nodes(){ return nodes_;}
};

void readPoints(const std::string& pointsFile, std::vector<Node>& nodes)
{
    std::ifstream file(pointsFile);
    if(!file.is_open())
    {
        std::cerr << "Error opening file: " << pointsFile << std::endl;
        return;
    }
    std::cout << "Successfully open the points file" << std::endl;

    // Consume the first 18 lines of the points file
    std::string line;
    for (int i = 0; i < 18; ++i)
    {
        std::getline(file, line);
    }

    int numberOfPoins(0);
    file >> numberOfPoins;
    // std::cout << "Number of points: " << numberOfPoins << std::endl;
    std::getline(file, line); // Consume the rest of the line
    std::getline(file, line); // To consume the next line

    nodes.resize(numberOfPoins);
    for (int i = 0; i < numberOfPoins; ++i)
    {
        char dummy;
        file >> dummy; // To consume the left parenthesis
        double x(0.0), y(0.0), z(0.0);
        file >> x >> y >> z;
        file >> dummy; // To consume the right parenthesis
        // file >> dummy; // To consume the newline character

        nodes[i].centroid = {x, y, z};
        nodes[i].index = i;
        nodes[i].iFaces = {};
        nodes[i].iElements = {};
    }


}

std::string getDirectory() {
    // Implement a function to get directory from user
    std::string caseDirectory;
    std::cout << "Enter the case directory: ";
    std::getline(std::cin, caseDirectory);
    return caseDirectory;
}

void cfdReadOpenFoamMesh(std::vector<Node>& nodes, std::string caseDirectory = "") {
    if (caseDirectory.empty()) {
        caseDirectory = getDirectory();
    }
    
    std::string pointsFile = caseDirectory + "/constant/polyMesh/points";
    std::string facesFile = caseDirectory + "/constant/polyMesh/faces";
    std::string ownerFile = caseDirectory + "/constant/polyMesh/owner";
    std::string neighbourFile = caseDirectory + "/constant/polyMesh/neighbour";
    std::string boundaryFile = caseDirectory + "/constant/polyMesh/boundary";
    
    // Add your file reading logic here
    readPoints(pointsFile, nodes);
}

int main(int argc, char* argv[]) {
    // std::cout << "Number of arguemnts: " << argc << std::endl;
    // for (int i = 0; i < argc; ++i)
    // {
    //     std::cout << "Command-line argument " << i << ":"  << argv[i] << std::endl;
    // }
    std::string caseDirectory(argv[1]);
    std::vector<Node> nodes;
    cfdReadOpenFoamMesh(nodes, caseDirectory);
    Mesh fvMesh{caseDirectory, nodes};
    // ------------------ Test ----------------------
    int precision = 10;
    for (int i = 0; i < 3; ++i)
    { 
        std::cout << std::fixed << std::setprecision(precision) << 
                    "(" << fvMesh.nodes()[i].centroid[0] << " " 
                        << fvMesh.nodes()[i].centroid[1] << " " 
                        << fvMesh.nodes()[i].centroid[2] << ")" << std::endl;
    }

    return 0;
}
