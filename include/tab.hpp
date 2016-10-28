#ifndef TAB_HPP
#define TAB_HPP

class tab{
	public:
		int 	lar;
		int 	alt;
		int 	cont;
		
		char** 	v;
		
		tab();
		tab(int largura, int altura);
		~tab();
		
		void 	operator=	(const tab&);
		bool 	operator==	(const tab&)const;
		
		int 	neigh		(int x, int y);
		void 	print		();
		void 	randomize	();
		
	private:
		void 	allocBoard	();
		void 	deallocBoard();
};

#endif