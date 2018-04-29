
import java.util.*;

/**
 * 
 */
public class Position {

	/**
	 * Default constructor
	 */
	public Position(double x,double y) {

		this.x=x;
		this.y=y;
	}

	public static Position getUnit(Position position,Position direction){

		double _x=position.x - direction.x;
		double _y=position.y - direction.y;

		double length=Math.sqrt(_x*_x + _y*_y);

		return new Position(_x / length,_y/length);
	}



	/**
	 * 
	 */
	public double x;

	/**
	 * 
	 */
	public double y;

	/**
	 * @return
	 */
	public int getX() {
		return (int)x;
	}

	/**
	 * @return
	 */
	public int getY() {
		// TODO implement here
		return (int)y;
	}

	/**
	 * @param other 
	 * @return
	 */
	public double distanceTo(Position other) {
		// TODO implement here
		return Math.sqrt( Math.pow(other.x -this.x,2) +  Math.pow(other.y -this.y,2)  );
	}

}