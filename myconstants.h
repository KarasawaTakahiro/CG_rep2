
/*
    �r�[�ʂɊւ����`
 */
#define MARBLE_SIZE 0.25
#define MARBLE_MAX_NUM 10
#define MARBLE_NOT_HIT -1

/*
    �u���b�N�Ɋւ����`
 */
#define BLOCK_SHOW 1
#define BLOCK_HIDE 0

/*
    �Փ˔���Ɋւ����`
 */
#define IS_HIT 1
#define NOT_HIT 0

/*
   ���f���̎�ނ������萔
 */
#define MODEL_TYPE_POST 100
#define MODEL_TYPE_STRAIGHT 101

#define MODEL_MAX_DEVISION 3  // ���f���̍ő啪����

/*
   �e���f���̐��l��\���萔
   ���^�Z�R�C�A��̎����l
 */

// ���p�[�c
#define POST_PATH "post_2.mqo"
#define POST_HEIGHT 50.0           // �ő�̍���
#define POST_WIDTH 34.0            // �ő�̕�
#define POST_INTERNAL_RADIUS 10.0  // �œ����̔��a
#define POST_OUTER_RADIUS 17.0     // �ŊO���̔��a

// �����p�[�c
#define STRAIGHT_PATH "straight.mqo"
#define STRAIGHT_HEIGHT 28.3  // �ō��_
#define STRAIGHT_WIDTH 160.5
#define STRAIGHT_DEPTH 20.0
#define STRAIGHT_RADIUS 10.0                   // �ʘH�̔��a
#define STRAIGHT_GROOVE_DEPTH 7.7             // �ʘH�̐[��
#define STRAIGHT_BASE_HIGHEST 18.6             // �ʘH�̒�ʂň�ԍ����_
#define STRAIGHT_BASE_LOWEST 1.3              // �ʘH�̒�ʂň�ԒႢ�_
#define STRAIGHT_OVERALL_LENGTH 160.5         // �ʘH�̒�ӂ̕�(z�����猩����ʂ̒���)
#define STRAIGHT_LENGTH_UPPER_SIDE 91.5       // �ʘH�̒�ӂ̕�(���S����オ���Ă�����̒[�܂�)
#define STRAIGHT_LENGTH_LOWER_SIDE 69.0       // �ʘH�̒�ӂ̕�(���S���牺�����Ă�����̒[�܂�)

// ���p�[�c�̓������
#define BRIDGE_ENTRANCE_PATH "bridge_entrance.mqo"
#define BRIDGE_ENTRANCE_CORRECTION_X 80.0  // ���p�[�c�̒��S�Ƃ��̃p�[�c�̒��S�����낦�鎞��X�������̕␳
#define BRIDGE_ENTRANCE_HIGHT 50.0                          // �ő�l
#define BRIDGE_ENTRANCE_WIDTH 34.0                          // �ő�l
#define BRIDGE_ENTRANCE_DEPTH 34.0                          // �ő�l
#define BRIDGE_ENTRANCE_INTERNAL_RADIUS 10.0                // �œ����̔��a
#define BRIDGE_ENTRANCE_OUTER_RADIUS 17.0                   // �ŊO���̔��a
#define BRIDGE_ENTRANCE_LOOKABLE_LENGTH_FROM_ORIGIN 63.0    // ���S�����������̒[�܂ł̒���

// ���p�[�c�̏o����
#define BRIDGE_OUTLET_PATH "bridge_outlet.mqo"
#define BRIDGE_OUTLET_CORRECTION_X -80.0                  // �␳�l
#define BRIDGE_OUTLET_HIGHT 50.0                            // �ő�l
#define BRIDGE_OUTLET_WIDTH 34.0                            // �ő�l
#define BRIDGE_OUTLET_DEPTH 34.0                            // �ő�l
#define BRIDGE_OUTLET_INTERNAL_RADIUS 10.0                  // �œ����̔��a
#define BRIDGE_OUTLET_OUTER_RADIUS 17.0                     // �ŊO���̔��a
#define BRIDGE_OUTLET_LOOKABLE_LENGTH_FROM_ORIGIN 63.0      // ���S����o�����̒[�܂ł̒���

