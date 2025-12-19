#include "../../include/products/PricingStrategy.hpp"

namespace minimarket {
namespace products {

PricingStrategy::PricingStrategy(const std::string& type, double markup)
    : strategyType(type), markupPercentage(markup) {}

double PricingStrategy::applyPricing(double costPrice) const {
    return costPrice * (1 + markupPercentage / 100);
}

bool PricingStrategy::validatePricing(double cost, double selling) const {
    return selling >= cost && selling <= cost * 3;
}

} // namespace products
} // namespace minimarket
