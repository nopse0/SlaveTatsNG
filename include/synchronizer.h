#pragma once

namespace slavetats_ng
{

	namespace synchronizer
	{

		struct sync_task
		{
			RE::FormID  _actor_id;
			uint32_t    _retry_num = 0;
		};

		class synchronizer : public singleton<synchronizer>
		{
			static constexpr size_t frames_count = 6;
			static constexpr size_t max_tries = 3;
			size_t                  frame_index = 0;
			size_t                  max_tasks_per_frame = 5;

			std::array<std::vector<sync_task>, frames_count> frames;

			void enqueue(sync_task a_task, size_t a_frame_delay);

		public:
			bool is_scheduled(RE::FormID a_actor_id) const;
			void schedule(RE::FormID a_actor_id, size_t a_frame_delay = 0);
			uint32_t process_frame();
	
		};

	}

}
