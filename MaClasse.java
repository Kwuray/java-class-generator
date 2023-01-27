/*comments*/
class MaClasse {

	/*attributes*/
	private synchronized int total;
	transient String x;
	protected double z;

	/*constructor*/
	public MaClasse(double z) {
		this.z = z;
	}

	/*getter total*/
	private int getTotal(){
		return this.total;
	}
	/*getter z*/
	protected double getZ(){
		return this.z;
	}

	/*setter total*/
	private int setTotal(){
		this.total = total;
	}
	/*setter z*/
	protected double setZ(){
		this.z = z;
	}
}