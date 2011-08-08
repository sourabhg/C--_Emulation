PROJECT = prj1
SRC_FILES = \
	test_correctness.cpp \
        test_speed.cpp 	\
	List_AnimalPtr.cpp \
	Animals.cpp \
	Animals.hpp \
	List_AnimalPtr.hpp \
	DynamicArray.hpp \
        Readme \
	makefile 


a.out:
	g++ -g Animals.cpp List_AnimalPtr.cpp test_correctness.cpp

#Removes all objects and executables.
clean:
	rm -f  *.out *.o  core *.core *~

#This target makes a archive containing all the project source files,
#suitable for submission.
submit:	$(SRC_FILES)
	tar cvfz $(PROJECT).tar.gz $(SRC_FILES)
