#include "synchronizer.h"

namespace main_loop {
 
    class main_update_hook
    {
    public:
        static constexpr int _frame_rate = 60;
		//static constexpr int _tick_interval_in_frames = _frame_rate * 3600 / controller::controller::timer_ticks_per_hour(); // 1 frame = 1/60th of a second (approx.)
        static constexpr int _tick_interval_in_frames = 1;

        static void hook()
        {
            // Target the precise interior call site within Main::PumpMessages (ID 35551 / 36544)
            // This completely bypasses the raw function entry bugs.
            REL::Relocation<std::uintptr_t> UpdateHook1{
                REL::VariantID(35551, 36544, 0x05B6D70),
                REL::VariantOffset(0x11F, 0x160, 0x11F)
            };

            auto& trampoline = SKSE::GetTrampoline();

            // Overwrite the specific 5-byte call site.
            // This naturally chains: If HDT-SMP loaded first, your _Update calls HDT.
            // If you loaded first, HDT's _Update will call you.
            _original_update_func = trampoline.write_call<5>(UpdateHook1.address(), &hook_update_func);

            logger::info("Successfully attached to the HDT-compliant Main Loop call site!");
        }

    private:
        // MUST match the HDT global function pattern exactly (No float delta parameter!)
        static void hook_update_func(RE::Main* const a_this)
        {
			static float _accumulated_play_time = 0.f;
            
            // 1. Always call the original engine function (or the next mod in the chain) first
            _original_update_func(a_this);
            
            //logger::info("hook_update_func: ModDisabled={}", ModDisabled);
            //if (ModDisabled)
            //    return;

            //auto tim = RE::BSTimer::GetSingleton();
            //_accumulated_play_time += tim->realTimeDelta; // naming is wrong, we accumulate wall-clock time, not play time
            
            // 2. Safely execute your plugin logic AFTER the frame has processed
            static uint32_t frame_count = 0;
            static uint32_t next_tick_count = 0;
			frame_count++;
            if (frame_count >= next_tick_count) {
				frame_count = 0;
                logger::trace("hook_update_func: emitting timer tick");
				next_tick_count = slavetats_ng::synchronizer::synchronizer::get_instance().process_frame();
				//_accumulated_play_time = 0.f;
            }
        }

        static inline REL::Relocation<decltype(&hook_update_func)> _original_update_func;
    };

    void install() {
        main_update_hook::hook();
    }

}
