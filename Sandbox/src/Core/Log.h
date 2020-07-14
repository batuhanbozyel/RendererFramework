#pragma once
#include <spdlog/spdlog.h>

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#define LOG_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__);
#define LOG_INFO(...) ::Log::GetLogger()->info(__VA_ARGS__);
#define LOG_WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__);
#define LOG_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__);
#define LOG_CRITICAL(...) ::Log::GetLogger()->critical(__VA_ARGS__);

#ifdef DEBUG_ENABLED
#define LOG_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define LOG_ASSERT(x, ...) x;
#endif