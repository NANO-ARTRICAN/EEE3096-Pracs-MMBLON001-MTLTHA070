/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "stm32f0xx.h"
#include <lcd_stm32f0.c>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// TODO: Add values for below variables
#define NS 256        // Number of samples in LUT
#define TIM2CLK 8000000  // STM Clock frequency
#define F_SIGNAL 250 // Frequency of output analog signal
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim2_ch1;

/* USER CODE BEGIN PV */
// TODO: Add code for global variables, including LUTs
int i = 0;
uint32_t Sin_LUT[NS] = {511.5, 524.1022944, 536.6969379, 549.2762845, 561.8326973, 574.3585533, 586.8462481, 599.2882005, 611.676857, 624.0046965, 636.2642349, 648.4480295, 660.5486834, 672.5588504, 684.4712393, 696.278618, 707.9738183, 719.5497402, 730.9993559, 742.3157144, 753.4919456, 764.5212644, 775.396975, 786.1124748, 796.6612585, 807.0369219, 817.233166, 827.2438007, 837.0627486, 846.6840486, 856.1018597, 865.3104644, 874.3042722, 883.0778229, 891.6257902, 899.9429847, 908.0243569, 915.8650008, 923.4601562, 930.8052123, 937.8957099, 944.7273443, 951.2959681, 957.5975935, 963.6283948, 969.3847108, 974.8630468, 980.0600769, 984.972646, 989.5977718, 993.9326463, 997.9746378, 1001.721293, 1005.170336, 1008.319674, 1011.167395, 1013.711769, 1015.951253, 1017.884487, 1019.510296, 1020.827694, 1021.835882, 1022.534247, 1022.922365, 1023, 1022.767106, 1022.223823, 1021.370482, 1020.207601, 1018.735885, 1016.956229, 1014.869712, 1012.477601, 1009.781349, 1006.782592, 1003.483151, 999.8850286, 995.99041, 991.8016591, 987.3213189, 982.5521095, 977.4969263, 972.1588381, 966.5410858, 960.6470799, 954.4803985, 948.0447855, 941.3441479, 934.3825536, 927.164229, 919.6935563, 911.9750708, 904.0134586, 895.813553, 887.3803321, 878.7189158, 869.8345623, 860.7326653, 851.4187506, 841.8984725, 832.1776108, 822.262067, 812.1578608, 801.8711264, 791.4081088, 780.7751602, 769.9787356, 759.0253896, 747.921772, 736.6746236, 725.2907726, 713.77713, 702.1406859, 690.3885045, 678.5277206, 666.5655348, 654.5092094, 642.3660636, 630.1434696, 617.8488476, 605.4896616, 593.0734149, 580.6076452, 568.0999206, 555.5578344, 542.9890009, 530.4010505, 517.8016254, 505.1983746, 492.5989495, 480.0109991, 467.4421656, 454.9000794, 442.3923548, 429.9265851, 417.5103384, 405.1511524, 392.8565304, 380.6339364, 368.4907906, 356.4344652, 344.4722794, 332.6114955, 320.8593141, 309.22287, 297.7092274, 286.3253764, 275.078228, 263.9746104, 253.0212644, 242.2248398, 231.5918912, 221.1288736, 210.8421392, 200.737933, 190.8223892, 181.1015275, 171.5812494, 162.2673347, 153.1654377, 144.2810842, 135.6196679, 127.186447, 118.9865414, 111.0249292, 103.3064437, 95.835771, 88.61744637, 81.65585207, 74.95521446, 68.51960145, 62.35292009, 56.45891415, 50.84116185, 45.50307371, 40.44789046, 35.67868109, 31.19834095, 27.00959005, 23.11497136, 19.51684929, 16.21740825, 13.21865131, 10.522399, 8.130288212, 6.043771186, 4.264114637, 2.792398987, 1.62951771, 0.776176786, 0.232894274, 0, 0.077635353, 0.4657532, 1.164117916, 2.172305528, 3.489703969, 5.115513451, 7.048746951, 9.288230812, 11.83260545, 14.68032619, 17.82966418, 21.27870749, 25.0253622, 29.06735374, 33.40222823, 38.02735399, 42.93992312, 48.13695322, 53.61528918, 59.37160515, 65.40240648, 71.70403189, 78.27265569, 85.1042901, 92.19478766, 99.53984376, 107.1349992, 114.9756431, 123.0570153, 131.3742098, 139.9221771, 148.6957278, 157.6895356, 166.8981403, 176.3159514, 185.9372514, 195.7561993, 205.766834, 215.9630781, 226.3387415, 236.8875252, 247.603025, 258.4787356, 269.5080544, 280.6842856, 292.0006441, 303.4502598, 315.0261817, 326.721382, 338.5287607, 350.4411496, 362.4513166, 374.5519705, 386.7357651, 398.9953035, 411.323143, 423.7117995, 436.1537519, 448.6414467, 461.1673027, 473.7237155, 486.3030621, 498.8977056, 511.5};

uint32_t saw_LUT[NS] = {0, 4.027559055, 8.05511811, 12.08267717, 16.11023622, 20.13779528, 24.16535433, 28.19291339, 32.22047244, 36.2480315, 40.27559055, 44.30314961, 48.33070866, 52.35826772, 56.38582677, 60.41338583, 64.44094488, 68.46850394, 72.49606299, 76.52362205, 80.5511811, 84.57874016, 88.60629921, 92.63385827, 96.66141732, 100.6889764, 104.7165354, 108.7440945, 112.7716535, 116.7992126, 120.8267717, 124.8543307, 128.8818898, 132.9094488, 136.9370079, 140.9645669, 144.992126, 149.019685, 153.0472441, 157.0748031, 161.1023622, 165.1299213, 169.1574803, 173.1850394, 177.2125984, 181.2401575, 185.2677165, 189.2952756, 193.3228346, 197.3503937, 201.3779528, 205.4055118, 209.4330709, 213.4606299, 217.488189, 221.515748, 225.5433071, 229.5708661, 233.5984252, 237.6259843, 241.6535433, 245.6811024, 249.7086614, 253.7362205, 257.7637795, 261.7913386, 265.8188976, 269.8464567, 273.8740157, 277.9015748, 281.9291339, 285.9566929, 289.984252, 294.011811, 298.0393701, 302.0669291, 306.0944882, 310.1220472, 314.1496063, 318.1771654, 322.2047244, 326.2322835, 330.2598425, 334.2874016, 338.3149606, 342.3425197, 346.3700787, 350.3976378, 354.4251969, 358.4527559, 362.480315, 366.507874, 370.5354331, 374.5629921, 378.5905512, 382.6181102, 386.6456693, 390.6732283, 394.7007874, 398.7283465, 402.7559055, 406.7834646, 410.8110236, 414.8385827, 418.8661417, 422.8937008, 426.9212598, 430.9488189, 434.976378, 439.003937, 443.0314961, 447.0590551, 451.0866142, 455.1141732, 459.1417323, 463.1692913, 467.1968504, 471.2244094, 475.2519685, 479.2795276, 483.3070866, 487.3346457, 491.3622047, 495.3897638, 499.4173228, 503.4448819, 507.4724409, 511.5, 515.5275591, 519.5551181, 523.5826772, 527.6102362, 531.6377953, 535.6653543, 539.6929134, 543.7204724, 547.7480315, 551.7755906, 555.8031496, 559.8307087, 563.8582677, 567.8858268, 571.9133858, 575.9409449, 579.9685039, 583.996063, 588.023622, 592.0511811, 596.0787402, 600.1062992, 604.1338583, 608.1614173, 612.1889764, 616.2165354, 620.2440945, 624.2716535, 628.2992126, 632.3267717, 636.3543307, 640.3818898, 644.4094488, 648.4370079, 652.4645669, 656.492126, 660.519685, 664.5472441, 668.5748031, 672.6023622, 676.6299213, 680.6574803, 684.6850394, 688.7125984, 692.7401575, 696.7677165, 700.7952756, 704.8228346, 708.8503937, 712.8779528, 716.9055118, 720.9330709, 724.9606299, 728.988189, 733.015748, 737.0433071, 741.0708661, 745.0984252, 749.1259843, 753.1535433, 757.1811024, 761.2086614, 765.2362205, 769.2637795, 773.2913386, 777.3188976, 781.3464567, 785.3740157, 789.4015748, 793.4291339, 797.4566929, 801.484252, 805.511811, 809.5393701, 813.5669291, 817.5944882, 821.6220472, 825.6496063, 829.6771654, 833.7047244, 837.7322835, 841.7598425, 845.7874016, 849.8149606, 853.8425197, 857.8700787, 861.8976378, 865.9251969, 869.9527559, 873.980315, 878.007874, 882.0354331, 886.0629921, 890.0905512, 894.1181102, 898.1456693, 902.1732283, 906.2007874, 910.2283465, 914.2559055, 918.2834646, 922.3110236, 926.3385827, 930.3661417, 934.3937008, 938.4212598, 942.4488189, 946.476378, 950.503937, 954.5314961, 958.5590551, 962.5866142, 966.6141732, 970.6417323, 974.6692913, 978.6968504, 982.7244094, 986.7519685, 990.7795276, 994.8070866, 998.8346457, 1002.862205, 1006.889764, 1010.917323, 1014.944882, 1018.972441, 1023, 0};

uint32_t triangle_LUT[NS] = {0, 4.976686843, 13.04397267, 21.11125849, 29.17854431, 37.24583013, 45.31311596, 53.38040178, 61.4476876, 69.51497342, 77.58225925, 85.64954507, 93.71683089, 101.7841167, 109.8514025, 117.9186884, 125.9859742, 134.05326, 142.1205458, 150.1878317, 158.2551175, 166.3224033, 174.3896891, 182.4569749, 190.5242608, 198.5915466, 206.6588324, 214.7261182, 222.7934041, 230.8606899, 238.9279757, 246.9952615, 255.0625473, 263.1298332, 271.197119, 279.2644048, 287.3316906, 295.3989765, 303.4662623, 311.5335481, 319.6008339, 327.6681198, 335.7354056, 343.8026914, 351.8699772, 359.937263, 368.0045489, 376.0718347, 384.1391205, 392.2064063, 400.2736922, 408.340978, 416.4082638, 424.4755496, 432.5428354, 440.6101213, 448.6774071, 456.7446929, 464.8119787, 472.8792646, 480.9465504, 489.0138362, 497.081122, 505.1484079, 513.2156937, 521.2829795, 529.3502653, 537.4175511, 545.484837, 553.5521228, 561.6194086, 569.6866944, 577.7539803, 585.8212661, 593.8885519, 601.9558377, 610.0231235, 618.0904094, 626.1576952, 634.224981, 642.2922668, 650.3595527, 658.4268385, 666.4941243, 674.5614101, 682.628696, 690.6959818, 698.7632676, 706.8305534, 714.8978392, 722.9651251, 731.0324109, 739.0996967, 747.1669825, 755.2342684, 763.3015542, 771.36884, 779.4361258, 787.5034117, 795.5706975, 803.6379833, 811.7052691, 819.7725549, 827.8398408, 835.9071266, 843.9744124, 852.0416982, 860.1089841, 868.1762699, 876.2435557, 884.3108415, 892.3781273, 900.4454132, 908.512699, 916.5799848, 924.6472706, 932.7145565, 940.7818423, 948.8491281, 956.9164139, 964.9836998, 973.0509856, 981.1182714, 989.1855572, 997.252843, 1005.320129, 1013.387415, 1021.454701, 1023, 1013.387415, 1005.320129, 997.252843, 989.1855572, 981.1182714, 973.0509856, 964.9836998, 956.9164139, 948.8491281, 940.7818423, 932.7145565, 924.6472706, 916.5799848, 908.512699, 900.4454132, 892.3781273, 884.3108415, 876.2435557, 868.1762699, 860.1089841, 852.0416982, 843.9744124, 835.9071266, 827.8398408, 819.7725549, 811.7052691, 803.6379833, 795.5706975, 787.5034117, 779.4361258, 771.36884, 763.3015542, 755.2342684, 747.1669825, 739.0996967, 731.0324109, 722.9651251, 714.8978392, 706.8305534, 698.7632676, 690.6959818, 682.628696, 674.5614101, 666.4941243, 658.4268385, 650.3595527, 642.2922668, 634.224981, 626.1576952, 618.0904094, 610.0231235, 601.9558377, 593.8885519, 585.8212661, 577.7539803, 569.6866944, 561.6194086, 553.5521228, 545.484837, 537.4175511, 529.3502653, 521.2829795, 513.2156937, 505.1484079, 497.081122, 489.0138362, 480.9465504, 472.8792646, 464.8119787, 456.7446929, 448.6774071, 440.6101213, 432.5428354, 424.4755496, 416.4082638, 408.340978, 400.2736922, 392.2064063, 384.1391205, 376.0718347, 368.0045489, 359.937263, 351.8699772, 343.8026914, 335.7354056, 327.6681198, 319.6008339, 311.5335481, 303.4662623, 295.3989765, 287.3316906, 279.2644048, 271.197119, 263.1298332, 255.0625473, 246.9952615, 238.9279757, 230.8606899, 222.7934041, 214.7261182, 206.6588324, 198.5915466, 190.5242608, 182.4569749, 174.3896891, 166.3224033, 158.2551175, 150.1878317, 142.1205458, 134.05326, 125.9859742, 117.9186884, 109.8514025, 101.7841167, 93.71683089, 85.64954507, 77.58225925, 69.51497342, 61.4476876, 53.38040178, 45.31311596, 37.24583013, 29.17854431, 21.11125849, 13.04397267, 4.976686843, 0};

// TODO: Equation to calculate TIM2_Ticks
uint32_t TIM2_Ticks = TIM2CLK/(NS*F_SIGNAL); // How often to write new LUT value
uint32_t DestAddress = (uint32_t) &(TIM3->CCR3); // Write LUT TO TIM3->CCR3 to modify PWM duty cycle

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);

/* USER CODE BEGIN PFP */
void EXTI0_1_IRQHandler(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)

{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  init_LCD();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();

  /* USER CODE BEGIN 2 */
  // TODO: Start TIM3 in PWM mode on channel 3
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);

  // TODO: Start TIM2 in Output Compare (OC) mode on channel 1.
  HAL_TIM_OC_Start(&htim2,TIM_CHANNEL_1);

  // TODO: Start DMA in IT mode on TIM2->CH1; Source is LUT and Dest is TIM3->CCR3; start with Sine LUT
  HAL_DMA_Start_IT(&hdma_tim2_ch1, Sin_LUT, DestAddress, NS);
  // TODO: Write current waveform to LCD ("Sine")

  delay(3000);
  lcd_command(CLEAR);
  lcd_putstring("Sine");

  // TODO: Enable DMA (start transfer from LUT to CCR)
  __HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }
  LL_SetSystemCoreClock(8000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = TIM2_Ticks - 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1023;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE0);

  /**/
  LL_GPIO_SetPinPull(Button0_GPIO_Port, Button0_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinMode(Button0_GPIO_Port, Button0_Pin, LL_GPIO_MODE_INPUT);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void EXTI0_1_IRQHandler(void)
{
	// TODO: Debounce using HAL_GetTick()
	HAL_GetTick();

	// TODO: Disable DMA transfer and abort IT, then start DMA in IT mode with new LUT and re-enable transfer
	// HINT: Consider using C's "switch" function to handle LUT changes
	__HAL_TIM_DISABLE_DMA(&htim2, TIM_DMA_CC1);
	HAL_DMA_Abort_IT(&hdma_tim2_ch1);
	if (i==0){
		i = i+1;
		delay(3000);
		lcd_command(CLEAR);
		lcd_putstring("Sawtooth");
		HAL_DMA_Start_IT(&hdma_tim2_ch1, saw_LUT, DestAddress, NS);
		__HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);
	}
	else if(i==1){
		i=i+1;
		delay(3000);
		lcd_command(CLEAR);
		lcd_putstring("Triangle");
		HAL_DMA_Start_IT(&hdma_tim2_ch1, triangle_LUT, DestAddress, NS);
		__HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);
	}
	else if(i==2){
		i=0;
		delay(3000);
		lcd_command(CLEAR);
		lcd_putstring("Sine");
		HAL_DMA_Start_IT(&hdma_tim2_ch1, Sin_LUT, DestAddress, NS);
		__HAL_TIM_ENABLE_DMA(&htim2, TIM_DMA_CC1);
	}

	HAL_GPIO_EXTI_IRQHandler(Button0_Pin); // Clear interrupt flags
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
