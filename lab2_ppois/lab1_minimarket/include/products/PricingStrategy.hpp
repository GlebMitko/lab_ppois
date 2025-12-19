#ifndef MINIMARKET_PRODUCTS_PRICINGSTRATEGY_HPP
#define MINIMARKET_PRODUCTS_PRICINGSTRATEGY_HPP

#include <string>

namespace minimarket {
namespace products {

class PricingStrategy {
public:
    PricingStrategy(const std::string& type, double markup);
    double applyPricing(double costPrice) const;
    bool validatePricing(double cost, double selling) const;

    const std::string& getStrategyType() const { return strategyType; }
    double getMarkupPercentage() const { return markupPercentage; }

private:
    std::string strategyType;
    double markupPercentage;
};

} // namespace products
} // namespace minimarket

#endif
