public abstract class OrderFactory {

    public OrderFactory() {
    }

    public abstract Order createOrder(Trader trader,int size);
}