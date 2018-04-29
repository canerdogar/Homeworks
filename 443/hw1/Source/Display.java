import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

public class Display extends JPanel {

	private Common common;

	public Display(Common common) {
		this.common=common;
		setBackground(Color.WHITE);
	}

	public Dimension getPreferredSize() {
		return new Dimension(super.getSize().width, super.getSize().height);
	}

	@Override
	public void paintComponent(Graphics g) {

		super.paintComponent(g);
		Graphics2D g2d=(Graphics2D)g;

		this.common.windowWidth = getPreferredSize().width;
		this.common.windowHeight = getPreferredSize().height;



		this.common.plot.draw(g2d);
		for(Trader t: this.common.traders) {
			t.draw(g2d);
		}
		for(Order o: this.common.orders) {
			o.draw(g2d);
		}
		for(ConMan c:this.common.Beginner){
			c.draw(g2d);
		}

		for(ConMan c:this.common.Novice){
			c.draw(g2d);
		}

		for(ConMan c:this.common.Master){
			c.draw(g2d);
		}

		for(ConMan c:this.common.Expert){
			c.draw(g2d);
		}

		this.common.ticker.draw(g2d);

	}
}