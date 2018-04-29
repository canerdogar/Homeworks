public class BuyOrderFactory extends OrderFactory {

    public BuyOrderFactory() {
    }

    @Override
    public Order createOrder(Trader trader,int size) {
        //Vector2D tempVect = Vector2D.randomVector(xLower, xUpper, yLower, yUpper);
        return new BuyOrder(trader,size);
    }
}