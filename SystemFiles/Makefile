CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = nursery_system
#test
SRCS =	Customer.cpp\
		AddToCart.cpp\
		BulkDiscount.cpp\
		CareIterator.cpp\
		CartIterator.cpp\
		CustomerCommand.cpp\
		DefaultRecomm.cpp\
		Invoker.cpp\
		Plant.cpp\
		PlantContainer.cpp\
		PriceRangeIterator.cpp\
		PricingStrategy.cpp\
		RecommStrategy.cpp\
		RegularPrice.cpp\
		RemoveFromCart.cpp\
		StratContext.cpp\
		SunlightRecomm.cpp\
		WaterRecomm.cpp\
		Command.cpp\
		InventorySystem.cpp\
		Iterator.cpp\
		PlantInventory.cpp\
		PlantIterator.cpp\
		main.cpp 

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

coverage: clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -fprofile-arcs -ftest-coverage"
	./$(TARGET)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html
	@echo "Coverage report generated in coverage_html/index.html"

clean:
	rm -f $(OBJS) $(TARGET) *.gcda *.gcno *.gcov coverage.info
	rm -rf coverage_html

.PHONY: all run clean valgrind coverage
