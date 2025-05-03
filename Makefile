compiler = g++
flags = -Wno-missing-field-initializers -std=c++11 -Wall -Wextra
# 源文件
objects = main.cpp \
       ui.cpp \
       DUE.cpp \
       user_control.cpp \
       health_system.cpp \
       score_system.cpp \
       All_maps/map1001.cpp \
       All_maps/map1117.cpp \
       All_maps/map1000.cpp \
       All_maps/map1016.cpp \
       All_maps/map2014.cpp \
       All_maps/map2601.cpp \
       All_maps/map_utils.cpp \
       Incidents/incidents.cpp \
       Incidents/reduce_health.cpp \
       Incidents/add_health.cpp \
       Incidents/pause_DUE.cpp \
       Incidents/add_time.cpp \
       Incidents/reverse_DUE.cpp \
       Incidents/reduce_time.cpp



# 最终目标
TARGET = game

# 链接目标
$(TARGET): $(objects)
	$(compiler) $(flags) $^ -o $@


# 清理规则
.PHONY: clean 

clean:
	rm -f $(TARGET)

