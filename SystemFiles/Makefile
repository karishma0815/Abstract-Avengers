CXX = g++
CXXFLAGS = -std=c++11 -Wall -DSUPPORT_TEST_TOGGLES
TARGET = nursery_system
TEST_TARGET = unit_test

SRCS =  Arrangement.cpp\
		CompleteNurseryUI.cpp\
		ConcreteArrangementBuilder.cpp\
		Director.cpp\
		ItemDecorator.cpp\
		DecorativePot.cpp\
		Customer.cpp\
		GiftWrap.cpp\
		Note.cpp\
		PlantItem.cpp\
		SalesContext.cpp\
		State.cpp\
		BrowsingState.cpp\
		AwaitingStockState.cpp\
		CartOpenState.cpp\
		SeekingAssistanceState.cpp\
		PendingPaymentState.cpp\
		PaymentAuthorizedState.cpp\
		PaymentFailedState.cpp\
		CompletedState.cpp\
		CancelledState.cpp\
		Plant.cpp\
		PlantState.cpp\
		SeedlingState.cpp\
		FloweringState.cpp\
		MatureState.cpp\
		ReadyForSaleState.cpp\
		SoldState.cpp\
		PlantContext.cpp\
		StockManager.cpp \
       	PlantFactory.cpp \
       	FlowerFactory.cpp \
       	SucculentFactory.cpp \
       	TreeFactory.cpp \
       	StockObserver.cpp \
       	StaffNotificationObserver.cpp \
       	InventoryObserver.cpp \
       	Flower.cpp \
       	Succulent.cpp \
       	Tree.cpp \
       	FlowerProduct.cpp \
       	SucculentProduct.cpp \
       	TreeProduct.cpp \
       	FlowerGroup.cpp \
       	SucculentGroup.cpp \
       	TreeGroup.cpp \
       	StockInventory.cpp \
       	Rose.cpp \
       	Lotus.cpp \
       	Protea.cpp \
       	Cacti.cpp \
       	Jade.cpp \
       	Orchid.cpp \
       	Pine.cpp \
       	Apple.cpp \
       	Jacaranda.cpp\
		WaterCommand.cpp \
		FertilizeCommand.cpp \
		PruneCommand.cpp \
		Gardener.cpp \
		Staff.cpp \
		SunlightCommand.cpp \
		PlantIssue.cpp \
		JuniorGardener.cpp \
		SeniorGardener.cpp \
		PlantSpecialist.cpp\
		PlantCareHandler.cpp \
		InventoryMediator.cpp \
		NurseryInventoryMediator.cpp \
		SalesAssistant.cpp \
		Manager.cpp \
		DeliveryStaff.cpp \
		CustomerQueryHandler.cpp \
		CustomerQuery.cpp \
		JuniorStaff.cpp \
		SalesExpert.cpp \
		PlantExpert.cpp \
		StaffFactory.cpp \
		GardenerFactory.cpp \
		SalesAssistantFactory.cpp \
		ManagerFactory.cpp \
		DeliveryStaffFactory.cpp\
		AddToCart.cpp\
		BulkDiscount.cpp\
		CartIterator.cpp\
		CustomerCommand.cpp\
		DefaultRecomm.cpp\
		Invoker.cpp\
		PlantContainer.cpp\
		PriceRangeIterator.cpp\
		PricingStrategy.cpp\
		Promotional.cpp\
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
		ArrangementsIterator.cpp\
		PlantAsItemAdapter.cpp\
		main.cpp 

OBJS = $(SRCS:.cpp=.o)

CORE_OBJS = $(filter-out main.o, $(OBJS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

test-%: %.cpp $(CORE_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $< $(CORE_OBJS)
	./$(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(CORE_OBJS)
	@echo "Please specify a test file. Usage: make test-<test_filename>"
	@echo "Example: make test-PlantTest.cpp"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

valgrind-test-%: %.cpp $(CORE_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $< $(CORE_OBJS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

coverage: clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -fprofile-arcs -ftest-coverage"
	./$(TARGET)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html
	@echo "Coverage report generated in coverage_html/index.html"

coverage-test-%: %.cpp
	$(MAKE) clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -fprofile-arcs -ftest-coverage" CORE_OBJS="$(CORE_OBJS)" test-$*
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html
	@echo "Coverage report for $* generated in coverage_html/index.html"

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET) *.gcda *.gcno *.gcov coverage.info
	rm -rf coverage_html

.PHONY: all run clean valgrind coverage test valgrind-test-% test-% coverage-test-%