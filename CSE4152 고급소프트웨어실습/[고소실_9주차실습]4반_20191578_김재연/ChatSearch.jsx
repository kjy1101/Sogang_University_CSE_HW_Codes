// 채팅 키워드 검색창 & 검색 버튼에 대한 컴포넌트 작성
import React, { useState } from "react";
import styled from "styled-components";
import TextField from "@material-ui/core/TextField";


function ChatSearch({ onSearchKeySubmit }) {

  const [KeywordState, setKeywordState] = useState("")

  const onKeywordChange = (e) => {
    setKeywordState(e.target.value)
  }

  const onKeywordSubmit = (e) => {
    e.preventDefault();
    onSearchKeySubmit(KeywordState);
    setKeywordState("");
}

  return (
      <form onSubmit={onKeywordSubmit}>
        <ChatSearchTag>
        <TextField
          name="keyword"
          onChange={(e) => onKeywordChange(e)}
          value={KeywordState}
          id="outlined-multiline-static"
          variant="outlined"
          label="keyword"
        />
        </ChatSearchTag>
        <Button>Search</Button>
      </form>
  );

}

const ChatSearchTag = styled.span`
  margin: 30px;
`;

const Button = styled.button`
  margin-top: 30px;
  padding: 10px;
  background-color: white;
  border-color: #c8a951;
  border-radius: 5px;
`;

//export {ChatSearch, Button}
export default ChatSearch;