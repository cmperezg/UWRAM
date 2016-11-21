(			i = j;
			j = i + 1;
			k = 1;
			p = 1;
		}
	}
	return std::make_tuple(i,p); // p is the period, i is the position of the suffix
}

int main(){
	std::tuple<int,int> res = maxsuffaz("mississauga");
	printf("suffix starts at %d \n",std::get<0>(res));
	return 0;
}