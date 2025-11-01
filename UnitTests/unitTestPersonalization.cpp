#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "PlantItem.h"
#include "DecorativePot.h"
#include "GiftWrap.h"
#include "Note.h"
#include "ConcreteArrangementBuilder.h"
#include "Director.h"

TEST_CASE("Builder + Decorator end-to-end using PlantItem") {
    // base product
    std::unique_ptr<Item> base(new PlantItem("Rose", 45.99, true));

    ConcreteArrangementBuilder builder;
    Director director;
    director.setBuilder(&builder);

    std::unique_ptr<Item> built = director.buildGiftWithNote(
        std::move(base),
        25.0, "Brown",          // pot
        10.0, "Happy Birthday", // wrap
        5.0,  "Enjoy!"          // note
    );

    REQUIRE(built.get() != nullptr);
    CHECK(built->readyForSale());
    CHECK(built->describe().find("Rose") != std::string::npos);
    CHECK(built->describe().find("Brown") != std::string::npos);
    CHECK(built->describe().find("Happy Birthday") != std::string::npos);
    CHECK(built->describe().find("Enjoy!") != std::string::npos);
    CHECK(doctest::Approx(built->priceFunc()) == (45.99 + 25 + 10 + 5));
}
