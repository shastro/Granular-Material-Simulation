/*
    Granular Simulation
    Author:Skyler Hughes
    Liscense: MIT
    Goals:

    - GUI ability to change to fullscreen
    - Ability to add cube's, circles, and apply forces on them


*/

#include "engine.hpp"
#include "ball.hpp"
#include "utils.hpp"
#include "sim.hpp"
#include <ctime>



int main(int argc, char **argv) {

    clock_t start;
    start = clock();

    const char *config_json;
    const char *config_path = "../config/engine-conf.json";

    // CONFIG PARSING //

        config_json = load_file(config_path);

        rj::Document configdoc;
        configdoc.Parse(config_json);

    // STRUCT INIT //

        struct window_t window;
        struct config_data_t config_st;

    // WINDOW DATA PARSING //

        window.width  = configdoc["window"]["width"].GetInt();
        window.height = configdoc["window"]["height"].GetInt();
        window.spawnbuffer = configdoc["window"]["spawnbuffer"].GetInt();

    // SIMULATION CONFIGURATION PARSING //

        config_st.FRAMELIMIT      = configdoc["FRAMELIMIT"].GetInt();
        config_st.SUB_FRAME_COUNT = configdoc["SUB_FRAME_COUNT"].GetInt();
        config_st.PARTICLE_COUNT  = configdoc["PARTICLE_COUNT"].GetInt();

        const char *SIM_FILENAME   = configdoc["SIM_FILENAME"].GetString();
        const char *SIM_FILEPATH   = configdoc["SIM_FILEPATH"].GetString();
        const char *COLLISION_MODE = configdoc["COLLISION_MODE"].GetString();

        if(strcmp(COLLISION_MODE, "HERTZ") == 0){
            config_st.COLLISION_MODE = HERTZ;
        }else if(strcmp(COLLISION_MODE, "HERTZ_DAMP") == 0){
            config_st.COLLISION_MODE = HERTZ_DAMP;
        }else {
            LOG("[ERROR]", "INVALID COLLISION_MODE")
            return 1;
        }

    // MEMORY FRAME SAVE THRESHOLD //

        config_st.MEMORY_FRAME_SAVE_THRESHOLD = configdoc["MEMORY_FRAME_SAVE_THRESHOLD"].GetInt();
        config_st.MINIMIZE_DATA = configdoc["MINIMIZE_DATA"].GetBool();

    // SPAWNING INFO //

        config_st.MIN_RADIUS = configdoc["MIN_RADIUS"].GetInt();
        config_st.MAX_RADIUS = configdoc["MAX_RADIUS"].GetInt();

    // TIMING //
        config_st.TIME_STEP_COEFFICIENT = configdoc["TIME_STEP_COEFFICIENT"].GetInt();
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
        dw.Uint((uint)config_st.FRAMELIMIT);

    // SUB FRAME COUNT //
        dw.Key("SUB_FRAME_COUNT");
        dw.Uint((uint)config_st.SUB_FRAME_COUNT);

    // SIM CONTACT MODE //

        dw.Key("SIN_CONTACT_MODE");
        dw.String(COLLISION_MODE); // Not a member of conf_st since we need the string version

    // PARTICLE COUNT //
        dw.Key("PARTICLE_COUNT");
        dw.Uint((uint)config_st.PARTICLE_COUNT);


    dw.Key("WINDOW_DATA");
    // Window Data //
    dw.StartObject();

        // Window Width //
        dw.Key("width");
        dw.Uint(window.width);

        // Window Height //
        dw.Key("height");
        dw.Uint(window.height);

        dw.Key("spawnbuffer");
        dw.Uint(window.spawnbuffer);


    dw.EndObject();


    // FILE NAMING AND CREATION //
    
    std::string filePath(SIM_FILEPATH);
    std::string fileName(SIM_FILENAME);
    std::string fileExtension(".json");
    std::string filePathName = filePath + fileName + fileExtension;
    FILE *dataout = fopen(filePathName.c_str(), "w");

    PRINT("\e[93m[STARTING SIM]\e[37m: " << "\e[92m" << fileName << "\e[37m")

    // ENGINE INSTANTIATION //
   Simulation_Engine *Engine = new Simulation_Engine(&window, &dw, &config_st);


    // Frame Data SetUp //
    dw.Key("FRAME_DATA");
    dw.StartArray();


    // MAIN FRAME LOOP //
    for(long i = 0; i < config_st.FRAMELIMIT; i++){

        dw.StartObject();

        dw.Key("f-num");
        dw.Uint(i);

        Engine->simLoop();

        if((i % config_st.MEMORY_FRAME_SAVE_THRESHOLD) == 0){
            printf("\n\e[91;50m[MEMORY DUMP]\e[37m");
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

    PRINT("\e[92m[SIMULATION COMPLETE]: \e[37m"  << "\e[92m" << fileName << "\e[37m");

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