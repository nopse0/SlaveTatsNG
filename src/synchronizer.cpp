#include "overlays.h"
#include "synchronizer.h"

namespace slavetats_ng
{

	namespace synchronizer
	{

		void synchronizer::enqueue(sync_task a_task, size_t a_frame_delay)
		{
			if (a_frame_delay >= frames_count) {
				a_frame_delay = frames_count - 1;
			}
			size_t target_slot = (frame_index + a_frame_delay) % frames_count;
			frames[target_slot].push_back(a_task);
		}

		bool synchronizer::is_scheduled(RE::FormID a_actor_id) const
		{
			for (const auto& slot : frames) {
				auto it = std::find_if(slot.begin(), slot.end(), [a_actor_id](const sync_task& t) {
					return t._actor_id == a_actor_id;
				});
				if (it != slot.end()) {
					return true;
				}
			}
			return false;
		}

		void synchronizer::schedule(RE::FormID a_actor_id, size_t a_frame_delay)
		{
			if (is_scheduled(a_actor_id)) {
				return;
			}
			enqueue(sync_task{ a_actor_id, 0 }, a_frame_delay);
		}

		uint32_t synchronizer::process_frame()
		{
			auto&  slot = frames[frame_index];
			size_t processed = 0;

			while (processed < max_tasks_per_frame && !slot.empty()) {
				auto task = slot.back();
				slot.pop_back();
				auto* actor = RE::TESForm::LookupByID<RE::Actor>(task._actor_id);
				if (!actor) {
					continue;
				}
				processed++;

				bool to_be_continued = false;
				auto err = synchronize_tattoos_internal(actor, &to_be_continued);
				if (!err && to_be_continued) {
					if (task._retry_num < max_tries) {
						task._retry_num++;
						enqueue(task, 3);
					}
				}
			}

			if (slot.empty()) {
				frame_index = (frame_index + 1) % frames_count;
			}

			return 1;
		}

	}

}
