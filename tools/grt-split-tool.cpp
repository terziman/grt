/**
 @author Nicholas Gillian <nick@nickgillian.com>
 @brief This file implements a basic tool for spliting data and saving the new data to two files.
*/

#include <GRT/GRT.h>
using namespace GRT;

InfoLog infoLog("[grt-split-tool]");
WarningLog warningLog("[WARNING grt-split-tool]");
ErrorLog errorLog("[ERROR grt-split-tool]");

bool printUsage(){
    infoLog << "grt-split-tool INPUT_FILENAME OUT_FILENAME_1 OUT_FILENAME_2" << endl;
    return true;
}

int main(int argc, char * argv[])
{

    if( argc != 4 ){
        errorLog << "Not enough input arguments!" << endl;
        printUsage();
        return EXIT_FAILURE;
    }

    const string inputFilename = argv[1];
    const string outputFilename1 = argv[2];
    const string outputFilename2 = argv[3];
    const unsigned int splitPercentage = 80;
    const bool useStratifiedSampling = true;

    infoLog << "- Loading main dataset: " << inputFilename << endl;

    ClassificationData data;
  
    //Load the raw data
    if( !data.load( inputFilename ) ){
        errorLog << "Failed to load input data: " << inputFilename << endl;
        return EXIT_FAILURE; 
    }

    infoLog << "- Loaded dataset with " << data.getNumSamples() << " samples" << endl;

    ClassificationData subset = data.partition( splitPercentage, useStratifiedSampling );

    infoLog << "- Data split. Stats:\n";
    infoLog << "- Main Dataset. Number of samples: " << data.getNumSamples() << endl;
    infoLog << "- Subset. Number of samples: " << subset.getNumSamples() << endl;
    infoLog << endl;

    //Save the new datasets
    if( !data.save( outputFilename1 ) ){
        errorLog << "Failed to save output data: " << outputFilename1 << endl;
        return EXIT_FAILURE; 
    }

    if( !subset.save( outputFilename2 ) ){
        errorLog << "Failed to save output data: " << outputFilename2 << endl;
        return EXIT_FAILURE; 
    }
    
    return EXIT_SUCCESS;
}

