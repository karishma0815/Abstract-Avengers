CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = nursery_system
#test
SRCS =  Arrangement.cpp \
		ConcreteArrangementBuilder.cpp \
		Director.cpp \
		ItemDecorator.cpp \
		DecorativePot.cpp \
		GiftWrap.cpp \
		Note.cpp \
		PlantItem.cpp \
		PrototypeRegistry.cpp \
		SalesOrder.cpp \
		State.cpp \
		BrowsingState.cpp \
		AwaitingStockState.cpp \
		CartOpenState.cpp \
		SeekingAssistanceState.cpp \
		PendingPaymentState.cpp \
		PaymentAuthorizedState.cpp \
		PaymentFailedState.cpp \
		CompletedState.cpp \
		CancelledState.cpp \
		Customer.cpp \
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
