#include "ResourceFile.h"

using namespace std;
using namespace GPL;

string ResourceFile::resource_file_name;

void ResourceFile::SetResourceFileName(const string& resource_file_name)
{
	ResourceFile::resource_file_name = resource_file_name;
}

streamoff ResourceFile::FileSize(ifstream& file)
{
	//Guardando a posição de GetPointer
	const streamoff position = file.tellg();

	//Colocando GetPointer no final do arquivo
	file.seekg(0,ios::end);

	//Pegando o tamanho do arquivo baseado na posição de GetPointer
	const streamoff size = file.tellg();

	//Reposicionando GetPointer como antes
	file.seekg(position);

	return size;
}

bool ResourceFile::Write(const string& new_resource_file_name)
{
	//Criando ou carregando o arquivo de recursos
	ofstream resource_file(ResourceFile::resource_file_name.c_str(),ios::binary | ios::app);

	//Carregando o novo arquivo que sera adicionado ao de recursos
	ifstream new_resource_file(new_resource_file_name.c_str(),ios::binary);

	//Verificando se os arquivos foram abertos
	if ((resource_file.is_open()) && (new_resource_file.is_open()))
	{
		const string& space = " ";
		resource_file << space.c_str() << setfill('0') << setw(9) << ResourceFile::FileSize(new_resource_file) << space.c_str() << new_resource_file.rdbuf();

		//Fechando os arquivos
		resource_file.close();
		new_resource_file.close();

		return true;
	}
	return false;
}

size_t ResourceFile::ReadBase(const int resource_id,const string& new_resource_file_name,unique_ptr<char[]>& memory_buffer,const bool use_memory_buffer)
{
	//Abrindo o arquivo de recursos
	ifstream resource_file(ResourceFile::resource_file_name.c_str(),ios::binary);

	//Verificando se o arquivo foi aberto
	if (resource_file.is_open())
	{
		int current_resource_id = 0;
		size_t total_size = 0;
		size_t found = 0;
		string string_buffer;

		//Enquanto não chegar ao fim do arquivo ou o arquivo desejado for encontrado
		while ((!resource_file.eof()) && (!found))
		{
			size_t file_size;

			//Pegando o tamanho do arquivo desse ID
			resource_file >> file_size;

			//Se for o ID escolhido
			if (current_resource_id == resource_id)
			{
				//Pulando um espaco de caractere ' '
				resource_file.seekg(static_cast<streamoff>(resource_file.tellg()) + 1);

				//Criando o buffer para criar o novo arquivo, adicionar um espaço para o '\0'
				unique_ptr<char[]> resource_buffer = make_unique<char[]>(file_size + 1);

				//Lendo para o buffer
				if (!resource_file.read(resource_buffer.get(),file_size))
					return 0;

				//Utilizando a memória como buffer do arquivo
				if (!use_memory_buffer)
				{
					//Criando o novo arquivo em branco
					ofstream new_resource_file(new_resource_file_name.c_str(),ios::binary);

					//Escrevendo para o arquivo
					if (!new_resource_file.write(resource_buffer.get(),file_size))
						return 0;

					//Fechando arquivo criado
					new_resource_file.close();
				}
				else
					memory_buffer = move(resource_buffer);

				//Arquivo encontrado e criado
				found = file_size;
			}
			else
			{
				//Tamanho + espaço + quantidade de caracteres do tamanho + espaço
				total_size += file_size + 1 + 9 + 1;
				resource_file.seekg(total_size);
				current_resource_id++;
			}
		}
		resource_file.close();
		return found;
	}
	return 0;
}

size_t ResourceFile::Read(const int resource_id,const string& new_resource_file_name)
{
	return ResourceFile::ReadBase(resource_id,new_resource_file_name,unique_ptr<char[]>(),false);
}

size_t ResourceFile::Read(const int resource_id,unique_ptr<char[]>& memory_buffer)
{
	return ResourceFile::ReadBase(resource_id,"",memory_buffer,true);
}