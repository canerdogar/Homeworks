public class SellOrderFactory extends OrderFactory {

    public SellOrderFactory() {
    }

    @Override
    public Order createOrder(Trader trader,int size) {
        //Vector2D tempVect = Vector2D.randomVector(xLower, xUpper, yLower, yUpper);
        return new SellOrder(trader,size);
    }
}