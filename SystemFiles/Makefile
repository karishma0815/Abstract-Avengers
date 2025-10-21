# -- Abstract Avengers Makefile --

CXX      = g++
CXXFLAGS = -Wall -std=c++11

TARGET = app

# Objects to link
OBJS = \
Arrangement.o \
ArrangementBuilder.o \
ConcreteArrangementBuilder.o \
Director.o \
Item.o \
ItemDecorator.o \
DecorativePot.o \
GiftWrap.o \
Note.o \
PlantItem.o \
PrototypeRegistry.o \
SalesOrder.o \
State.o \
BrowsingState.o \
AwaitingStockState.o \
CartOpenState.o \
SeekingAssistanceState.o \
PendingPaymentState.o \
PaymentAuthorizedState.o \
PaymentFailedState.o \
CompletedState.o \
CancelledState.o \
Customer.o \
main.o

make: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# -- Taskeen's Files --

Arrangement.o: Arrangement.cpp Arrangement.h Item.h
	$(CXX) $(CXXFLAGS) -c Arrangement.cpp

ArrangementBuilder.o: ArrangementBuilder.h
	@echo "Header-only: ArrangementBuilder.h"
	@touch ArrangementBuilder.o

ConcreteArrangementBuilder.o: ConcreteArrangementBuilder.cpp ConcreteArrangementBuilder.h ArrangementBuilder.h Item.h
	$(CXX) $(CXXFLAGS) -c ConcreteArrangementBuilder.cpp

Director.o: Director.cpp Director.h ArrangementBuilder.h Item.h Arrangement.h
	$(CXX) $(CXXFLAGS) -c Director.cpp

Item.o: Item.h
	@echo "Header-only: Item.h"
	@touch Item.o

ItemDecorator.o: ItemDecorator.cpp ItemDecorator.h Item.h
	$(CXX) $(CXXFLAGS) -c ItemDecorator.cpp

DecorativePot.o: DecorativePot.cpp DecorativePot.h ItemDecorator.h Item.h
	$(CXX) $(CXXFLAGS) -c DecorativePot.cpp

GiftWrap.o: GiftWrap.cpp GiftWrap.h ItemDecorator.h Item.h
	$(CXX) $(CXXFLAGS) -c GiftWrap.cpp

Note.o: Note.cpp Note.h ItemDecorator.h Item.h
	$(CXX) $(CXXFLAGS) -c Note.cpp

PlantItem.o: PlantItem.cpp PlantItem.h Item.h
	$(CXX) $(CXXFLAGS) -c PlantItem.cpp

PrototypeRegistry.o: PrototypeRegistry.cpp PrototypeRegistry.h Item.h
	$(CXX) $(CXXFLAGS) -c PrototypeRegistry.cpp

SalesOrder.o: SalesOrder.cpp SalesOrder.h State.h Customer.h
	$(CXX) $(CXXFLAGS) -c SalesOrder.cpp

State.o: State.cpp State.h SalesOrder.h Customer.h
	$(CXX) $(CXXFLAGS) -c State.cpp

BrowsingState.o: BrowsingState.cpp BrowsingState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c BrowsingState.cpp

AwaitingStockState.o: AwaitingStockState.cpp AwaitingStockState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c AwaitingStockState.cpp

CartOpenState.o: CartOpenState.cpp CartOpenState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c CartOpenState.cpp

SeekingAssistanceState.o: SeekingAssistanceState.cpp SeekingAssistanceState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c SeekingAssistanceState.cpp

PendingPaymentState.o: PendingPaymentState.cpp PendingPaymentState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c PendingPaymentState.cpp

PaymentAuthorizedState.o: PaymentAuthorizedState.cpp PaymentAuthorizedState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c PaymentAuthorizedState.cpp

PaymentFailedState.o: PaymentFailedState.cpp PaymentFailedState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c PaymentFailedState.cpp

CompletedState.o: CompletedState.cpp CompletedState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c CompletedState.cpp

CancelledState.o: CancelledState.cpp CancelledState.h State.h SalesOrder.h
	$(CXX) $(CXXFLAGS) -c CancelledState.cpp

Customer.o: Customer.cpp Customer.h
	$(CXX) $(CXXFLAGS) -c Customer.cpp

# -- Main File --

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

run: make
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
