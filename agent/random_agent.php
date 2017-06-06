<?php

/**
 * Пример простого агента
 * случайного хода
 */
class MySimpleAgent {

	// адрес сервера
	public $url;
	// пассивные действия агента (повороты-развороты, бездействие)
	public $passivMoves;
	// активные действия агента (шаг вперед, выстрел, взятие клада, бездействие)
	public $activMoves;
	// кол-во стрел агента
	public $arrowcount;
	// пещеры в которых агент побывал
	public $knowCaves = [];

	/**
	 *  Конструктор
	 */
	public function __construct() {
		$this->url			 = 'https://mooped.net/local/its/index.php?module=game&action=agentaction';
		$this->passivMoves	 = ['onLeft', 'onRight', 'upSideDn', 'noAct'];
		$this->activMoves	 = ['Go', 'Shoot', 'Take', 'noAct'];
	}

	/**
	 * Метод для соединения с сервером
	 * @param int		$id			- идентификатор попытки игры
	 * @param int		$userid		- идентификатор пользователя
	 * @param string	$act		- действия агента на текущем шагу
	 *
	 * @return object	$data->text					- объект с данными
	 * 					$data->text->currentcave	- информация о текущей пещере
	 * 					$data->text->worldinfo		- информация о мире
	 * 					$data->text->iagent			- информация об агенте
	 * 					$data->text->userid			- идентификатор пользователя
	 */
	public function connect($id, $userid, $act = 'noAct noAct') {
		$ch = curl_init();

		// GET запрос указывается в строке URL
		curl_setopt($ch, CURLOPT_URL, $this->url . "&gameid=" . $id . "&userid=" . $userid . "&act=" . urlencode($act));
		curl_setopt($ch, CURLOPT_HEADER, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 30);
		curl_setopt($ch, CURLOPT_USERAGENT, 'PHP MySimpleAgent');
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		$curl_data = curl_exec($ch);
		curl_close($ch);

		$data = json_decode($curl_data);

		if (isset($data->error) && $data->error) {
			//error_type == 'notification' пропускаем
			//это уведомления о невозможности действий^
			//нет стрел, чтобы стрелять
			//нельзя идти вперед, потому что стена
			//взять клад, поскольку его нет в пещере
			if (!isset($data->error_type)) {
				$data->error_type = 'error';
			}

			if ($data->error_type == 'error') {
				print_r($data->error);
				die;
			}
		}

		if (!is_object($data)) {
			print_r($curl_data);
			die;
		}

		return $data->text;
	}

	/**
	 * Метод для получения хода агента (пассив. + актив. действия) из текущего состояния
	 * @param object $currentCave	- текущая пещера агента
	 *
	 * @return string			- ход агента на данной итерации
	 */
	public function chooseAct($currentCave) {

		//Если в текущей пещере золото
		//Взять клад
		if ($currentCave->isGold == 1) {
			return 'noAct Take';
		}

		//Запись в массив известных пещер текущей пещеры
		$this->knowCaves[$currentCave->cNum] = $currentCave;

		//Случайным образом выбираем пассивное действие и активное действие агента на данном ходе
		return $this->passivMoves[array_rand($this->passivMoves)] . ' ' . $this->activMoves[array_rand($this->activMoves)];
	}

	/**
	 * Метод начала работы агента
	 * @param int	$id		- идентификатор попытки игры
	 * @param int	$userid	- идентификатор пользователя
	 * @param string	$act		- действия агента на текущем шагу
	 */
	public function runAct($id, $userid, $act = 'noAct noAct') {

		$resp = $this->connect($id, $userid, $act);

		//Агент уперся в стену,
		//Не осталось стрел
		//Получение информации о мире
		if (is_null($resp)) {
			return $this->runAct($id, $userid, 'noAct noAct');
		}
		if (!is_object($resp)) {
			print_r($resp);
			die;
		}

		//Данные для более 'умных' агентов
		$this->arrowcount		 = $resp->iagent->arrowcount;
		$this->worldInfo		 = (array) $resp->worldinfo;
		$this->IAStateUtilities	 = (array) $resp->iagent->IAStateUtilities;

		//Если золото не найдено
		//Выбор и выполнение следующего хода агента
		if (isset($resp->worldinfo->isgoldfinded) && $resp->worldinfo->isgoldfinded == 0) {
			$newAct = $this->chooseAct($resp->currentcave);
			return $this->runAct($id, $userid, $newAct);
		}
		else {
			print_r($resp);
			print_r('Золото найдено');
			die;
		}
	}

}

//Параметры: идентификатор игры и идентифкатор пользователя


$id	= null;
if (isset($_GET['id']))
	$id = filter_input(INPUT_GET, 'id', FILTER_VALIDATE_INT);
elseif (isset($_POST['id']))
	$id = filter_input(INPUT_POST, 'id', FILTER_VALIDATE_INT);

$userid	= null;
if (isset($_GET['userid']))
	$userid = filter_input(INPUT_GET, 'userid', FILTER_VALIDATE_INT);
elseif (isset($_POST['userid']))
	$userid = filter_input(INPUT_POST, 'userid', FILTER_VALIDATE_INT);


//Проверка на наличие параметров
if (empty($id) || is_null($id)) {
	print_r('Invalid id param');
	die;
}
if (empty($userid) || is_null($userid)) {
	print_r('Invalid userid param');
	die;
}

//Инициализация агента
$myAgent = new MySimpleAgent();
//Запуск работы агента
$myAgent->runAct($id, $userid); // передаем id игры и userid
//Запускать так, например:
//http://localhost/random_agent.php?id=41&userid=2
