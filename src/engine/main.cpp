/*
    Granular Simulation
    Author:Skyler Hughes
    Liscense: MIT
    Goals:

    - GUI ability to change to fullscreen
    - Ability to add cube's, circles, and apply forces on them


*/

#include "main.hpp"
#include "ball.hpp"
#include "utils.hpp"
#include "sim.hpp"
#include <ctime>

char* load_file(char const* path)
{
    char* buffer = 0;
    long length;
    FILE * f = fopen (path, "rb"); //was "rb"

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = (char*)malloc ((length + 1) * sizeof(char));
        if (buffer)
        {
            fread (buffer, sizeof(char), length, f);
        }
        fclose (f);
    }else{
        PRINT("[ERROR]: UNABLE TO LOAD CONFIG FILE")
    }
    buffer[length] = '\0';
    return buffer;
}


int main(int argc, char **argv) {

    clock_t start;
    start = clock();

    const char *config_json;
    const char *config_path = "../config/engine-conf.json";

    // CONFIG PARSING //

    config_json = load_file(config_path);

    rj::Document configdoc;
    configdoc.Parse(config_json);


    // WINDOW DATA PARSING //

    struct window_t window;
    struct config_data_t config_struct;

    window.width  = configdoc["window"]["width"].GetInt();
    window.height = configdoc["window"]["height"].GetInt();

    // SIMULATION CONFIGURATION PARSING //

        int FRAMELIMIT      = configdoc["FRAMELIMIT"].GetInt();
        int SUB_FRAME_COUNT = configdoc["SUB_FRAME_COUNT"].GetInt();
        int PARTICLE_COUNT  = configdoc["PARTICLE_COUNT"].GetInt();

        const char *SIM_FILENAME   = configdoc["SIM_FILENAME"].GetString();
        const char *SIM_FILEPATH   = configdoc["SIM_FILEPATH"].GetString();
        const char *COLLISION_MODE = configdoc["COLLISION_MODE"].GetString();

        int C_MODEL = HERTZ; //Default Collision Model

        if(strcmp(COLLISION_MODE, "HERTZ") == 0){
            C_MODEL = HERTZ;
        }else if(strcmp(COLLISION_MODE, "HERTZ_DAMP") == 0){
            C_MODEL = HERTZ_DAMP;
        }

    // MEMORY FRAME SAVE THRESHOLD //

        int MEMORY_FRAME_SAVE_THRESHOLD = configdoc["MEMORY_FRAME_SAVE_THRESHOLD"].GetInt();

        config_struct.MINIMIZE_DATA = configdoc["MINIMIZE_DATA"].GetBool();

    // Close Config //
        free((void *)config_json);


    /////////////////////////////////////////////
    // DATA GENERATION - END OF CONFIG PARSING //
    /////////////////////////////////////////////

    // Document Instantiation //

    rj::StringBuffer docbuffer;
    rj::Writer<rj::StringBuffer> dw(docbuffer);

    dw.StartObject();
    // HEADER VALUES //

    // FILENAME //

        dw.Key("SIM_NAME");
        dw.String(SIM_FILENAME);

    // SIM DATE //

        dw.Key("SIM_DATE");
        dw.String("TEMP_DATE");


    // FRAMELIMIT //
        dw.Key("FRAMELIMIT");
        dw.Uint(FRAMELIMIT);

    // SUB FRAME COUNT //
        dw.Key("SUB_FRAME_COUNT");
        dw.Uint(SUB_FRAME_COUNT);

    // SIM CONTACT MODE //

        dw.Key("SIN_CONTACT_MODE");
        dw.String(COLLISION_MODE);

    // PARTICLE COUNT //
        dw.Key("PARTICLE_COUNT");
        dw.Uint(PARTICLE_COUNT);


    dw.Key("WINDOW_DATA");
    // Window Data //
    dw.StartObject();

        // Window Width //
        dw.Key("width");
        dw.Uint(window.width);

        // Window Height //
        dw.Key("height");
        dw.Uint(window.height);


    dw.EndObject();



    // ENGINE INSTANTIATION //
   Simulation_Engine *Engine = new Simulation_Engine(SUB_FRAME_COUNT, PARTICLE_COUNT, &window, C_MODEL, &dw, &config_struct);

   



    // FILE NAMEING AND CREATION //
    std::string filePath(SIM_FILEPATH);
    std::string fileName(SIM_FILENAME);
    std::string fileExtension(".json");
    std::string filePathName = filePath + fileName + fileExtension;
    FILE *dataout = fopen(filePathName.c_str(), "w");

    // Frame Data SetUp //
    dw.Key("FRAME_DATA");
    dw.StartArray();

    // MAIN FRAME LOOP //
    for(long i = 0; i < FRAMELIMIT; i++){

        dw.StartObject();

        dw.Key("f-num");
        dw.Uint(i);

        Engine->simLoop();

        if((i % MEMORY_FRAME_SAVE_THRESHOLD) == 0){
            printf("\nMEMORY DUMP");
            fprintf(dataout, "%s", docbuffer.GetString());
            fflush(dataout);
            docbuffer.Flush();
            docbuffer.Clear();
            docbuffer.ShrinkToFit();
            //dw.Reset(docbuffer);
        }
        
        dw.EndObject();

        printf("\nFRAME: %ld COMPLETE\n", i);
    }

    dw.EndArray();
    // WRITING TO FILE //

    //End Wrapper Object
    dw.EndObject();

    fprintf(dataout, "%s", docbuffer.GetString());
    fflush(dataout);

    
    printf("SIMULATION COMPLETE!\n");

    clock_t end;
    end = clock();

    PRINT("COMPLETION TIME: "<< (double)(end - start)/ CLOCKS_PER_SEC << "seconds")
    // clean up :)
    delete Engine;
    dw.Reset(docbuffer);
    docbuffer.Clear();
    docbuffer.ShrinkToFit();
    fclose(dataout);
    return 0;
}