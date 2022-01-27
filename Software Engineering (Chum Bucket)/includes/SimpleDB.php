<?php declare(strict_types=1);


class SimpleDB
{
    private mysqli $dblink;


    public function __construct()
    {

    }

    public function close(): void
    {
        $this->dblink->close();
    }

    public function setLink(mysqli $link) : void
    {
        $this->dblink = $link;
    }

    public function getLink() : mysqli
    {
        return $this->dblink;
    }

    /**
     * Read configuration from xml file.
     * @param string $db_fn
     * @return object|null
     */
    public static function getDBConfig(string $db_fn) : ?object
    {
        if (!file_exists($db_fn))
        {
            printf("Cannot find file: %s\n", $db_fn);
            exit();
        }

        $xml = simplexml_load_string(file_get_contents($db_fn))->db;
        if ($xml)
        {
            return $xml;
        }
        return null;
    }


    /**
     * Set DB connection.
     * @param string $hostname
     * @param string $username
     * @param string $password
     * @param string $database
     */
    public function setDBConnection(string $hostname, string $username, string $password, string $database) : void
    {
        $this->dblink = new mysqli($hostname, $username, $password, $database);

        if ($this->dblink->connect_errno) {
            printf("Connect failed: %s\n", $this->dblink->connect_error);
            exit();
        }
    }


    /**
     * @param string $query
     * @param string $type
     * @param array $params
     * @return mysqli_result|null
     */
    public function bind(string $query, string $type, array $params) : ?mysqli_result
    {
        $stmt = $this->dblink->prepare($query);
        $stmt->bind_param($type, ...$params);
        $stmt->execute();
        $result = $stmt->get_result();
        if($result)
        {
            return $result;
        }
        return null;
    }

    /**
     * Simple function for seeding one row in a table.
     * @param string $table
     * @param array $row
     * @param string $type
     * @return bool
     */
    public function seedTableRow(string $table, array $row, string $type) : bool
    {
        //echo array_map(static fn($r) => $r->value, json_encode(array_values($row)));
        $columns = implode(',', array_keys($row));

        $placeholders = str_split(str_repeat('?', count($row)));
        $values = implode(',', $placeholders);
        $sql_query = "INSERT INTO $table ($columns) VALUES ($values)";
        $result = $this->bind($sql_query, $type, array_values($row));
        if ($result)
        {
            return true;
        }
        return false;
    }

    /**
     * Simple TearDown Routine for DB seeds.
     * @param string $table
     * @param string $condition
     * @return bool
     */
    public function tearDownTable(string $table, string $condition) : bool
    {
        $sql_query = "DELETE FROM $table WHERE $condition";
        return $this->dblink->query($sql_query);
    }

}