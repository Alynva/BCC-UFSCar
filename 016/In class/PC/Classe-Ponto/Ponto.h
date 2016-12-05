class Ponto {
	private:
//		bool declared;
		int x;
		int y;
		char id;
		static char contId;
		
	public:
		Ponto(int = 0, int = 0);
		
		int getX() const;
		int getY() const;
		char getId() const;
//		bool getDeclared() const;

		bool setX(int);
		bool setY(int);

		void operator=(Ponto);
		
		void delPoint();
		friend Ponto middPoint(Ponto, Ponto);
		friend bool isColli(Ponto, Ponto, Ponto);
		friend double distPoints(Ponto, Ponto);

		void print();

		const static int rows = 19; // 39
		const static int cols = 39; // 79
};
