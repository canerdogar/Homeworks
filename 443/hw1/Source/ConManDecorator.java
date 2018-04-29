import java.awt.Graphics2D;

public abstract class ConManDecorator extends ConMan {

    public ConMan decoratedConman;

    public ConManDecorator(ConMan decoratedConman) {
        super();
        this.decoratedConman = decoratedConman;
    }



}