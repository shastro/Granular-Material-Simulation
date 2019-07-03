/*
    Granular Simulation
    Author:Skyler Hughes
    Liscence: MIT
    Goals:

    - GUI ability to change to fullscreen
    - Ability to add cube's, circles, and apply forces on them


*/

#include "basic.hpp"
#include "ball.hpp"
#include "utils.hpp"
#include "sim.hpp"

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
    }
    buffer[length] = '\0';
    return buffer;
}


int main(int argc, char **argv) {

    const char *config_json;
    const char *config_path = "../config.json";

    // CONFIG PARSING //

    config_json = load_file(config_path);

    rj::Document configdoc;
    configdoc.Parse(config_json);


    // WINDOW DATA PARSING //

    struct window_t *window = (window_t *)malloc(sizeof(struct window_t));
    window->width  = configdoc["window"]["width"].GetInt();
    window->height = configdoc["window"]["height"].GetInt();

    // SIMULATION CONFIGURATION PARSING //

        int FRAMELIMIT      = configdoc["FRAMELIMIT"].GetInt();
        int SUB_FRAME_COUNT = configdoc["SUB_FRAME_COUNT"].GetInt();
        int PARTICLE_COUNT  = configdoc["PARTICLE_COUNT"].GetInt();

        const char *SIM_FILENAME   = configdoc["SIM_FILENAME"].GetString();
        const char *COLLISION_MODE = configdoc["COLLISION_MODE"].GetString();
        
        int C_MODEL = HERTZ; //Default Collision Model

        if(strcmp(COLLISION_MODE, "HERTZ") == 0){
            C_MODEL = HERTZ;
        }else if(strcmp(COLLISION_MODE, "HERTZ_DAMP")){
            C_MODEL = HERTZ_DAMP;
        }

    // DATA FILE PARSiNG and INITIALIZATION//

        const char *data_json = "";
        const char *data_path = "../simulation_data/";

    // Document Instantiation //

        rj::Document datadoc;
        datadoc.SetObject();
        rj::Document::AllocatorType& allocator = datadoc.GetAllocator();

    // HEADER VALUES //

    // FILENAME
        rj::Value sim_fname;

        char buffer[50];
        strncpy(buffer, SIM_FILENAME, strlen(SIM_FILENAME));

        sim_fname.SetString(buffer, strlen(SIM_FILENAME), allocator);
        datadoc.AddMember("SIM_NAME", sim_fname, allocator);

        memset(buffer, 0, sizeof(buffer));

        datadoc.AddMember("SIM_DATE", "TEMP_DATE", allocator);

    // SIM CONTACT MODE //

    // Window Data //
    rj::Value window_data(rj::kObjectType);

        // Window Width //
        rj::Value window_width;
        window_width.SetInt(window->width);
        window_data.AddMember("width", window_width, allocator);

        // Window Height //
        rj::Value window_height;
        window_height.SetInt(window->height);
        window_data.AddMember("height", window_height, allocator);

        // Adding Window Data
        datadoc.AddMember("WINDOW_DATA", window_data, allocator);

    // Frame Data SetUp //
    rj::Value frame_data(rj::kArrayType);


    // ENGINE INSTANTIATION //

   // Simulation_Engine *Engine = new Simulation_Engine(SUB_FRAME_COUNT, PARTICLE_COUNT, window, C_MODEL, sj::Document *datadoc);

    // MAIN FRAME LOOP //
    for(long i = 0; i < FRAMELIMIT; i++){
       // Engine->simLoop();
    }


    // WRITING TO FILE //

    FILE *dataout = fopen("../simulation_data/test.json", "w");

    char writeBuffer[65536];
    rj::FileWriteStream os(dataout, writeBuffer, sizeof(writeBuffer));
    rj::PrettyWriter<rj::FileWriteStream> writer(os);
    datadoc.Accept(writer);

    // clean up :)
    //delete Engine;
    fclose(dataout);
    free((void *)window);
    free((void *)config_json);
    return 0;
}