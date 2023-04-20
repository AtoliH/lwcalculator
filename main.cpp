#include <iostream>
#include <lwlib/Analyzer.hpp>
#include <lwlib/TurnAction.hpp>
#include <lwlib/FastDevice.hpp>
#include <numeric>
#include <fstream>
#include <sstream>
#include <ev.h>
#include <amqpcpp.h>
#include <amqpcpp/libev.h>
#include <nlohmann/json.hpp>
// todo Remove json dependence from here and call parser with json string
#include "Parser.h"
using json = nlohmann::json;

#include "data.h"

std::vector<cl_uint> fetch_optimal_story_cards(lw_character touhou_friend, lw_character enemy, std::vector<story_card> sc_collection);

template <unsigned int D>
class NDRange : public cl::NDRange
{
private:
    template<int index, typename T0, typename... T1s>
    void setSizes(T0&& t0, T1s&&... t1s)
    {
        sizes_[index] = t0;
        setSizes<index + 1, T1s...>(std::forward<T1s>(t1s)...);
    }

    template<int index, typename T0>
    void setSizes(T0&& t0)
    {
        sizes_[index] = t0;
    }

    template<int index>
    void setSizes()
    {
    }

public:
    template<typename... Ts, std::enable_if_t<D == sizeof...(Ts) && D <= NDRange_MAX_DIMENSIONS>* = nullptr>
    NDRange(Ts... ts)
    {
        dimensions_ = D;
        setSizes<0>(std::forward<Ts>(ts)...);
    }
};


void handleMessage(const AMQP::Message &message) {
    std::cout << std::string(message.body(), message.bodySize()) << std::endl;

    json data = json::parse(message.body(), message.body() + message.bodySize());

    Character character = Parser::characterFromJson(data);
}

int main() {
    // access to the event loop
    auto *loop = EV_DEFAULT;

    // handler for libev (so we don't have to implement AMQP::TcpHandler!)
    AMQP::LibEvHandler handler(loop);

    // make a connection
    AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://localhost/"));

    // we need a channel too
    AMQP::TcpChannel channel(&connection);

    // create a temporary queue
    channel.declareQueue("lwstrategizer",0).onSuccess([&connection, &channel](const std::string &name, uint32_t messagecount, uint32_t consumercount) {

        // report the name of the temporary queue
        std::cout << "declared queue " << name << std::endl;

        channel.consume(name)
                .onReceived([&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
                    handleMessage(message);
                    channel.ack(deliveryTag);
                });
    });

    // run the loop
    ev_run(loop, 0);

    // Deep analysis
    /**
     * innacurate damage: 29739/0
     * consistency: 0
     * exact consistency: 1
     */
    /*std::vector<TurnAction> turns = {
            TurnAction(TurnAction::secondSpellCard, TurnAction::noBoost, TurnAction::grazeOnce),
            TurnAction(TurnAction::firstSpellCard, TurnAction::noBoost, TurnAction::grazeOnce),
            TurnAction(TurnAction::thirdSpellCard, TurnAction::boostOnce, TurnAction::grazeOnce, TurnAction::midTarget, TurnAction::firstSkill, TurnAction::secondSkill),
            TurnAction(TurnAction::fourthSpellCard, TurnAction::boostOnce, TurnAction::grazeOnce, TurnAction::midTarget, TurnAction::thirdSkill),
            TurnAction(TurnAction::lastWord, TurnAction::boostThrice, TurnAction::grazeOnce)
    };

    std::vector<TurnAction> turnsAlt(36);
    std::fill(turnsAlt.begin(), turnsAlt.end(), TurnAction(TurnAction::firstSpellCard));


    Character hongMeiling(lwdata::meiling);
    Character witchOfScarletDreams(lwdata::witch);

    Character::StoryCard boo(Character::YangAttack, 68, Character::YinAttack, 72, std::make_pair(ModifierType::YinAttack, Modifier<ModifierType::Stat>(2, 2)));
    Character::StoryCard itsSpring(Character::YangAttack, 72, Character::YangDefense, 68);
    Character::StoryCard poltergeistSistersConcer(Character::YangDefense, 90, Character::YinDefense, 90, Modifier(ModifierType::Accuracy, 3, 2));
    Character::StoryCard unknownBarrierTeam(Character::YangAttack, 70, Character::YinAttack, 80, Modifier(ModifierType::BulletEnergy, 50, 1), Modifier(ModifierType::YangAttack, 2, 1));
    Character::StoryCard unknownBarrierTeam6(Character::YangAttack, 50, Character::YinAttack, 60, Modifier(ModifierType::BulletEnergy, 25, 1), Modifier(ModifierType::YangAttack, 1, 1));

    hongMeiling.equip(TurnAction::firstSpellCard, boo);
    hongMeiling.equip(TurnAction::secondSpellCard, itsSpring);
    hongMeiling.equip(TurnAction::thirdSpellCard, itsSpring);
    hongMeiling.equip(TurnAction::fourthSpellCard, poltergeistSistersConcer);
    hongMeiling.equip(TurnAction::lastWord, unknownBarrierTeam);
    Analyzer::analyzeTurnsConsistency(turns, hongMeiling, witchOfScarletDreams);*/

    return 0;

    /*auto out = fetch_optimal_story_cards(lwdata::meiling, lwdata::witch, std::vector<story_card>({ SC_BOO, SC_ITS_SPRING, SC_ITS_SPRING, SC_POLTERGEIST_SISTERS_CONCERT, SC_UNKNOWN_BARRIER_TEAM }));
    std::cout << "Result: " << std::endl;
    std::vector<int> strat(5*5*5);
    std::iota(strat.begin(), strat.end(), 0);
    std::sort(strat.begin(), strat.end(), [&out](int a, int b) {
        return out[a] < out[b];
    });
    //int i = min_strat_id; // expected 115 (0,3,4) rn yields 71k because acc
    for (int j = 0; j < out.size(); j++)
    {
        int i = strat[j];

        int global_id_1 = i % 5;
        int rem = (i - global_id_1)/5;
        int global_id_2 = rem % 5;
        rem -= global_id_2;
        int global_id_3 = rem / 5;

        auto scid_to_str = [](int id) {
            switch (id) {
                case 0:
                    return "A CURIOUS FESTIVAL";
                case 1:
                case 2:
                    return "IT'S SPRING";
                case 3:
                    return "POLTERGEIST SISTERS CONCERT";
                case 4:
                    return "UNKNOWN BARRIER TEAM";
            }
            return "UNKNOWN STORY CARD";
        };

        std::cout << "#" << i << " (" << global_id_1 << "," << global_id_2 << "," << global_id_3 << "): " << out[i] << " with " << scid_to_str(global_id_1) << ", IT'S SPRING, IT'S SPRING, " << scid_to_str(global_id_2) << " and " << scid_to_str(global_id_3) << std::endl;
    }

    return 0;*/
}

std::vector<cl_uint>
fetch_optimal_story_cards(lw_character touhou_friend, lw_character enemy, std::vector<story_card> sc_collection) {
    // get all platforms (drivers), e.g. NVIDIA
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);

    if (all_platforms.size()==0) {
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

    // get default device (CPUs, GPUs) of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }

    // use device[1] because that's a GPU; device[0] is the CPU
    cl::Device default_device=all_devices[1];
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
    std::cout << "Max number of dimensions: " << default_device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>() << "\n";
    std::cout << "Max workgroup size: " << default_device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>() << "\n";

    // a context is like a "runtime link" to the device and platform;
    // i.e. communication is possible
    cl::Context context({default_device});

    // create the program that we want to execute on the device
    cl::Program::Sources sources;

    std::string total_code = FastDevice::getMacro() + FastDevice::getTypes() + FastDevice::getDmgcalc();
    sources.push_back({total_code.c_str(), total_code.length()});

    cl::Program program(context, sources);
    if (program.build({default_device}) != CL_SUCCESS) {
        std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
        exit(1);
    }

    unsigned long sc_collection_size = sc_collection.size();
    constexpr int party_size = 1;
    constexpr int number_of_enemies = 1;

    cl::Buffer buffer_SC(context, CL_MEM_READ_ONLY, sizeof(story_card) * sc_collection_size);
    cl::Buffer buffer_FRIENDS(context, CL_MEM_READ_ONLY, sizeof(lw_character) * party_size);
    cl::Buffer buffer_ENNEMIES(context, CL_MEM_READ_ONLY, sizeof(lw_character) * number_of_enemies);
    cl::Buffer buffer_OUT(context, CL_MEM_READ_WRITE, sizeof(cl_uint) * 5*5*5);

    story_card * SC = sc_collection.data();
    lw_character FRIENDS[party_size] = { touhou_friend };
    lw_character ENNEMIES[number_of_enemies] = { enemy };

    cl::CommandQueue queue(context, default_device);

    queue.enqueueWriteBuffer(buffer_SC, CL_TRUE, 0, sizeof(story_card) * sc_collection_size, SC);
    queue.enqueueWriteBuffer(buffer_FRIENDS, CL_TRUE, 0, sizeof(lw_character) * party_size, FRIENDS);
    queue.enqueueWriteBuffer(buffer_ENNEMIES, CL_TRUE, 0, sizeof(lw_character) * number_of_enemies, ENNEMIES);

    cl::KernelFunctor<cl::Buffer, cl::Buffer, cl::Buffer, cl::Buffer> dmg_calc(program, "dmg_calc");
    dmg_calc(cl::EnqueueArgs(queue, NDRange<3>(0,3,4), NDRange<3>(1,1,1), NDRange<3>(1,1,1)), buffer_SC, buffer_FRIENDS, buffer_ENNEMIES, buffer_OUT);

    // read result from GPU to here
    std::vector<cl_uint> out(5*5*5);
    queue.enqueueReadBuffer(buffer_OUT, CL_TRUE, 0, sizeof(cl_uint)*5*5*5, out.data());

    return out;
}

