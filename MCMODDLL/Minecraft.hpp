/*
���ļ����Minecraft�ڲ���������õ������ݽṹ��������;���ƣ�����Ľṹ���ܲ�������
���δ���汾������1.16.0.2�汾�����µ������ݽṹ�仯���������з�����������
*/
#pragma once


using VA = unsigned __int64;
using RVA = unsigned long int;

template<typename Type>
using Ptr = Type*;

template<typename T>
struct SharedPtr {
	auto get() {
		return **reinterpret_cast<T***>(this);
	}
	auto operator->() {
		return get();
	}
};

struct BlockLegacy {
	// ��ȡ������
	auto getFullName() const {
		return  *(std::string*)((VA)this + 112);
	}

	// ��ȡ����ID��
	auto getBlockItemId() const {
		short v3 = *(short*)((VA)this + 268);
		if (v3 < 0x100) {
			return v3;
		}
		return (short)(255 - v3);
	}

};

struct BlockPos {
	// ��ȡ��������ͷ
	INT32* getPosition() const {
		return reinterpret_cast<INT32*>(reinterpret_cast<VA>(this));
	}
};

struct Block {
	// ��ȡԴ
	const BlockLegacy* getLegacyBlock() const {
		return (BlockLegacy*)(**((VA**)this + 2));
	}
};

struct BlockActor {
	// ȡ����
	Block* getBlock() {
		return *reinterpret_cast<Block**>(reinterpret_cast<VA>(this) + 16);
	}
	// ȡ����λ��
	BlockPos* getPosition() {
		return reinterpret_cast<BlockPos*>(reinterpret_cast<VA>(this) + 44);
	}
};

struct BlockSource {
	// ȡ����
	Block* getBlock(const BlockPos* blkpos) {
		return SYMCALL(Block *,
			"?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z",
			this, blkpos);
	}
};

struct Vec3 {
	float x;
	float y;
	float z;
};

struct Actor {
	// ȡ����Դ
	BlockSource* getRegion() {
		return *reinterpret_cast<BlockSource**>(reinterpret_cast<VA>(this) + 414*sizeof(void*));
	}
	// ȡά��ID
	int getDimension() {
		return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 204);
	}
	// ȡ���ֱ�ǩ
	const std::string* getNameTag() const {
		return SYMCALL(const std::string *,
			"?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			this);
	}
	// �Ƿ�����
	const byte isStand() {
		return *reinterpret_cast<byte *>(reinterpret_cast<VA>(this) + 416);
	}
	// ȡ���λ��
	Vec3* getPos() {
		return SYMCALL(Vec3 *,
			"?getPos@Actor@@UEBAAEBVVec3@@XZ",
			this);
	}
};
struct Mob
	:Actor {
};
struct Player
	:Mob {
};

struct GameMode {

};

struct ContainerManagerModel {
	// ȡ������
	Player* getPlayer() {
		return *reinterpret_cast<Player**>(reinterpret_cast<VA>(this) + 8);
	}
};
struct LevelContainerManagerModel
	:ContainerManagerModel {
};

struct ItemStack {
	// ȡ��ƷID
	int getId() {
		return SYMCALL(short,
			"?getId@ItemStackBase@@QEBAFXZ",
			this);
	}
	// ȡ��Ʒ����
	std::string getName() {
		std::string str;
		SYMCALL(VA,
			"?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			this, &str);
		return str;
	}

	// ȡ����������
	int getCount() {
		return *((char*)this + 34);
	}
};

struct LevelContainerModel {
	// ȡ��������
	Player* getPlayer() {
		return ((Player**)this)[26];
	}
};
