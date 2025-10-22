CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = nursery_system
#test
SRCS =  Arrangement.cpp\
		ConcreteArrangementBuilder.cpp\
		Director.cpp\
		ItemDecorator.cpp\
		DecorativePot.cpp\
		GiftWrap.cpp\
		Note.cpp\
		PlantItem.cpp\
		PrototypeRegistry.cpp\
		SalesOrder.cpp\
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
		Customer.cpp\
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
		Promotional.cpp\
		RecommStrategy.cpp\
		Regularprice.cpp\
		RemoveFromCart.cpp\
		StratContext.cpp\
		SunlightRecomm.cpp\
		WaterRecomm.cpp\
		Flower.cpp\
		FlowerFactory.cpp\
		FlowerGroup.cpp\
		FlowerProduct.cpp\
		InventoryObserver.cpp\
		PlantFactory.cpp\
		StaffNotificationObserver.cpp\
		StockManager.cpp\
		StockObserver.cpp\
		Succulent.cpp\
		SucculentFactory.cpp\
		SucculentGroup.cpp\
		SucculentProduct.cpp\
		Tree.cpp\
		TreeFactory.cpp\
		TreeGroup.cpp\
		TreeProduct.cpp\
		Aggregate.cpp\
		Command.cpp\
		CustomerQuery.cpp\
		CustomerQueryHandler.cpp\
		DeliveryStaff.cpp\
		DeliveryStaffFactory.cpp\
		FertilizeCommand.cpp\
		FloweringState.cpp\
		Gardener.cpp\
		GardenerFactory.cpp\
		InventoryMediator.cpp\
		InventorySystem.cpp\
		Iterator.cpp\
		JuniorGardener.cpp\
		JuniorStaff.cpp\
		Manager.cpp\
		ManagerFactory.cpp\
		MatureState.cpp\
		NurseryInventoryMediator.cpp\
		PlantCareHandler.cpp\
		PlantContext.cpp\
		PlantExpert.cpp\
		PlantInventory.cpp\
		PlantIssue.cpp\
		PlantIterator.cpp\
		PlantSpecialist.cpp\
		PlantState.cpp\
		PruneCommand.cpp\
		ReadyForSaleState.cpp\
		SalesAssistant.cpp\
		SalesAssistantFactory.cpp\
		SalesExpert.cpp\
		SeedlingState.cpp\
		SeniorGardener.cpp\
		SoldState.cpp\
		Staff.cpp\
		StaffFactory.cpp\
		SunlightCommand.cpp\
		WaterCommand.cpp\
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
